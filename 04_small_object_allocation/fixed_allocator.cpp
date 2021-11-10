#include <cassert>
#include <iostream>
#include <vector>

struct Chunk {
  void Init(std::size_t blockSize, unsigned char blocks) {
    pData_ = new unsigned char[blockSize * blocks]();
    firstAvailableBlock_ = 0;
    blocksAvailable_ = blocks;
    unsigned char i = 0;
    unsigned char *p = pData_;
    for (; i != blocks; p += blockSize) {
      *p = ++i;
    }
  }

  unsigned char *Allocate(std::size_t blockSize) {
    if (!blocksAvailable_)
      return 0;
    unsigned char *pResult = pData_ + (firstAvailableBlock_ * blockSize);
    firstAvailableBlock_ = *pResult;
    --blocksAvailable_;
    return pResult;
  }

  void Deallocate(unsigned char *p, std::size_t blockSize) {
    assert(p >= pData_);
    unsigned char *toRelease = static_cast<unsigned char *>(p);
    assert((toRelease - pData_) % blockSize == 0);
    *toRelease = firstAvailableBlock_;
    firstAvailableBlock_ =
        static_cast<unsigned char>((toRelease - pData_) / blockSize);
    // assert(firstAvailableBlock_ == (toRelease - pData_) / blockSize);
    ++blocksAvailable_;
  }

  void Destroy() {
    delete[] pData_;
    pData_ = nullptr;
  }

  unsigned char *pData_;
  unsigned char firstAvailableBlock_, blocksAvailable_;
};

struct FixedAllocator {

  unsigned char *Allocate() {
    if (allocChunk_ == 0 || allocChunk_->blocksAvailable_ == 0) {
      auto i = chunks_.begin();
      for (;; ++i) {
        if (i == chunks_.end()) {
          chunks_.reserve(chunks_.size() + 1);
          Chunk newChunk;
          newChunk.Init(blockSize_, numBlocks_);
          chunks_.push_back(newChunk);
          allocChunk_ = &chunks_.back();
          deallocChunk_ = &chunks_.back();
          break;
        }
        if (i->blocksAvailable_ > 0) {
          allocChunk_ = &*i;
          break;
        }
      }
    }
    assert(allocChunk_ != 0);
    assert(allocChunk_->blocksAvailable_ > 0);
    return allocChunk_->Allocate(blockSize_);
  }

  void Deallocate(unsigned char *p) {
    deallocChunk_->Deallocate(p, blockSize_);
  }

  void Destroy() {
    for (auto &ch : chunks_) {
      ch.Destroy();
    }
  }

  std::size_t blockSize_ = 8;
  unsigned char numBlocks_ = 8;
  std::vector<Chunk> chunks_{};
  Chunk *allocChunk_ = nullptr;
  Chunk *deallocChunk_ = nullptr;
};

auto main() -> int {
  FixedAllocator fa;

  auto memory1 = fa.Allocate();
  auto memory2 = fa.Allocate();

  *memory1 = '1';
  *memory2 = '2';

  std::cout << "Memory layout ";

  for (size_t i = 0; i < 16; i++) {
    std::cout << *(memory1 + i) << ", ";
  }

  std::cout << std::endl;

  fa.Deallocate(memory2);
  fa.Deallocate(memory1);

  fa.Destroy();

  return 0;
}
