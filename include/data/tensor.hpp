// MIT License
// Copyright (c) 2022 - 傅莘莘
// Source URL: https://github.com/zjhellofss/KuiperInfer
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// Created by fss on 22-11-12.

#ifndef KUIPER_INFER_DATA_BLOB_HPP_
#define KUIPER_INFER_DATA_BLOB_HPP_
#include <glog/logging.h>
#include <armadillo>
#include <memory>
#include <vector>

namespace kuiper_infer {
template <typename T>
class Tensor {
 public:
  explicit Tensor() = default;

  /**
   * 创建张量
   * @param channels 张量的通道数
   * @param rows 张量的行数
   * @param cols 张量的列数
   */
  explicit Tensor(uint32_t channels, uint32_t rows, uint32_t cols);

  /**
   * 创建一个一维向量
   * @param size 一维向量中元素的个数
   */
  explicit Tensor(uint32_t size);

  /**
   * 创建一个二维向量
   * @param rows 二维向量的高度
   * @param cols 二维向量的宽度
   */
  explicit Tensor(uint32_t rows, uint32_t cols);

  /**
   * 创建张量
   * @param shapes 张量的维度
   */
  explicit Tensor(const std::vector<uint32_t>& shapes);

  /**
   * 返回张量的行数
   * @return 张量的行数
   */
  uint32_t rows() const;

  /**
   * 返回张量的列数
   * @return 张量的列数
   */
  uint32_t cols() const;

  /**
   * 返回张量的通道数
   * @return 张量的通道数
   */
  uint32_t channels() const;

  /**
   * 返回张量中元素的数量
   * @return 张量的元素数量
   */
  uint32_t size() const;

  /**
   * 设置张量中的具体数据
   * @param data 数据
   */
  void set_data(const arma::Cube<T>& data);

  /**
   * 设置张量中的具体数据
   * @param data 数据
   */
  void set_data(arma::Cube<T>&& data);

  /**
   * 返回张量是否为空
   * @return 张量是否为空
   */
  bool empty() const;

  /**
   * 返回张量中offset位置的元素
   * @param offset 需要访问的位置
   * @return offset位置的元素
   */
  T index(uint32_t offset) const;

  /**
   * 返回张量中offset位置的元素
   * @param offset 需要访问的位置
   * @return offset位置的元素
   */
  T& index(uint32_t offset);

  /**
   * 张量的尺寸大小
   * @return 张量的尺寸大小
   */
  std::vector<uint32_t> shapes() const;

  /**
   * 张量的实际尺寸大小
   * @return 张量的实际尺寸大小
   */
  const std::vector<uint32_t>& raw_shapes() const;

  /**
   * 返回张量中的数据
   * @return 张量中的数据
   */
  arma::Cube<T>& data();

  /**
   * 返回张量中的数据
   * @return 张量中的数据
   */
  const arma::Cube<T>& data() const;

  /**
   * 返回张量第channel通道中的数据
   * @param channel 需要返回的通道
   * @return 返回的通道
   */
  arma::Mat<T>& slice(uint32_t channel);

  /**
   * 返回张量第channel通道中的数据
   * @param channel 需要返回的通道
   * @return 返回的通道
   */
  const arma::Mat<T>& slice(uint32_t channel) const;

  /**
   * 返回特定位置的元素
   * @param channel 通道
   * @param row 行数
   * @param col 列数
   * @return 特定位置的元素
   */
  T at(uint32_t channel, uint32_t row, uint32_t col) const;

  /**
   * 返回特定位置的元素
   * @param channel 通道
   * @param row 行数
   * @param col 列数
   * @return 特定位置的元素
   */
  T& at(uint32_t channel, uint32_t row, uint32_t col);

  /**
   * 填充张量
   * @param pads 填充张量的尺寸
   * @param padding_value 填充张量
   */
  void Padding(const std::vector<uint32_t>& pads, T padding_value);

  /**
   * 使用value值去初始化向量
   * @param value
   */
  void Fill(T value);

  /**
   * 使用values中的数据初始化张量
   * @param values 用来初始化张量的数据
   */
  void Fill(const std::vector<T>& values, bool row_major = true);

  /**
   * 返回Tensor内的所有数据
   * @param row_major 是否是行主序列的
   * @return Tensor内的所有数据
   */
  std::vector<T> values(bool row_major = true);

  /**
   * 以常量1初始化张量
   */
  void Ones();

  /**
   * 以随机值初始化张量，符合正态分布
   */
  void RandN(T mean = 0, T var = 1);

  /**
   * 以随机值初始化张量
   */
  void RandU(T min = 0, T max = 1);

  /**
   * 打印张量
   */
  void Show();

  /**
   * 张量的实际尺寸大小的Reshape pytorch兼容
   * @param shapes 张量的实际尺寸大小
   * @param row_major 根据行主序还是列主序进行reshape
   */
  void Reshape(const std::vector<uint32_t>& shapes, bool row_major = false);

  /**
   * 展开张量
   */
  void Flatten(bool row_major = false);

  /**
   * 对张量中的元素进行过滤
   * @param filter 过滤函数
   */
  void Transform(const std::function<T(T)>& filter);

  /**
   * 返回数据的原始指针
   * @return 返回数据的原始指针
   */
  T* raw_ptr();

  /**
   * 返回数据的原始指针
   * @param offset 数据指针的偏移量
   * @return 返回数据的原始指针
   */
  T* raw_ptr(uint32_t offset);

  /**
   * 返回第index个矩阵的起始地址
   * @param index 第index个矩阵
   * @return 第index个矩阵的起始地址
   */
  T* matrix_raw_ptr(uint32_t index);

 private:
  std::vector<uint32_t> raw_shapes_;  // 张量数据的实际尺寸大小
  arma::Cube<T> data_;                // 张量数据
};

template <typename T>
Tensor<T>::Tensor(uint32_t channels, uint32_t rows, uint32_t cols) {
  data_ = arma::Cube<T>(rows, cols, channels);
  if (channels == 1 && rows == 1) {
    this->raw_shapes_ = std::vector<uint32_t>{cols};
  } else if (channels == 1) {
    this->raw_shapes_ = std::vector<uint32_t>{rows, cols};
  } else {
    this->raw_shapes_ = std::vector<uint32_t>{channels, rows, cols};
  }
}

template <typename T>
Tensor<T>::Tensor(uint32_t size) {
  data_ = arma::Cube<T>(1, size, 1);
  this->raw_shapes_ = std::vector<uint32_t>{size};
}

template <typename T>
Tensor<T>::Tensor(uint32_t rows, uint32_t cols) {
  data_ = arma::Cube<T>(rows, cols, 1);
  if (rows == 1) {
    this->raw_shapes_ = std::vector<uint32_t>{cols};
  } else {
    this->raw_shapes_ = std::vector<uint32_t>{rows, cols};
  }
}

template <typename T>
Tensor<T>::Tensor(const std::vector<uint32_t>& shapes) {
  CHECK(!shapes.empty() && shapes.size() <= 3);

  uint32_t remaining = 3 - shapes.size();
  std::vector<uint32_t> shapes_(3, 1);
  std::copy(shapes.begin(), shapes.end(), shapes_.begin() + remaining);

  uint32_t channels = shapes_.at(0);
  uint32_t rows = shapes_.at(1);
  uint32_t cols = shapes_.at(2);

  data_ = arma::Cube<T>(rows, cols, channels);
  if (channels == 1 && rows == 1) {
    this->raw_shapes_ = std::vector<uint32_t>{cols};
  } else if (channels == 1) {
    this->raw_shapes_ = std::vector<uint32_t>{rows, cols};
  } else {
    this->raw_shapes_ = std::vector<uint32_t>{channels, rows, cols};
  }
}

template <typename T>
uint32_t Tensor<T>::rows() const {
  CHECK(!this->data_.empty());
  return this->data_.n_rows;
}

template <typename T>
uint32_t Tensor<T>::cols() const {
  CHECK(!this->data_.empty());
  return this->data_.n_cols;
}

template <typename T>
uint32_t Tensor<T>::channels() const {
  CHECK(!this->data_.empty());
  return this->data_.n_slices;
}

template <typename T>
uint32_t Tensor<T>::size() const {
  CHECK(!this->data_.empty());
  return this->data_.size();
}

template <typename T>
void Tensor<T>::set_data(const arma::Cube<T>& data) {
  CHECK(data.n_rows == this->data_.n_rows)
      << data.n_rows << " != " << this->data_.n_rows;
  CHECK(data.n_cols == this->data_.n_cols)
      << data.n_cols << " != " << this->data_.n_cols;
  CHECK(data.n_slices == this->data_.n_slices)
      << data.n_slices << " != " << this->data_.n_slices;
  this->data_ = data;
}

template <typename T>
bool Tensor<T>::empty() const {
  return this->data_.empty();
}

template <typename T>
T Tensor<T>::index(uint32_t offset) const {
  CHECK(offset < this->data_.size()) << "Tensor index out of bound!";
  return this->data_.at(offset);
}

template <typename T>
T& Tensor<T>::index(uint32_t offset) {
  CHECK(offset < this->data_.size()) << "Tensor index out of bound!";
  return this->data_.at(offset);
}

template <typename T>
std::vector<uint32_t> Tensor<T>::shapes() const {
  CHECK(!this->data_.empty());
  return {this->channels(), this->rows(), this->cols()};
}

template <typename T>
arma::Cube<T>& Tensor<T>::data() {
  return this->data_;
}

template <typename T>
const arma::Cube<T>& Tensor<T>::data() const {
  return this->data_;
}

template <typename T>
arma::Mat<T>& Tensor<T>::slice(uint32_t channel) {
  CHECK_LT(channel, this->channels());
  return this->data_.slice(channel);
}

template <typename T>
const arma::Mat<T>& Tensor<T>::slice(uint32_t channel) const {
  CHECK_LT(channel, this->channels());
  return this->data_.slice(channel);
}

template <typename T>
T Tensor<T>::at(uint32_t channel, uint32_t row, uint32_t col) const {
  CHECK_LT(row, this->rows());
  CHECK_LT(col, this->cols());
  CHECK_LT(channel, this->channels());
  return this->data_.at(row, col, channel);
}

template <typename T>
T& Tensor<T>::at(uint32_t channel, uint32_t row, uint32_t col) {
  CHECK_LT(row, this->rows());
  CHECK_LT(col, this->cols());
  CHECK_LT(channel, this->channels());
  return this->data_.at(row, col, channel);
}

template <typename T>
void Tensor<T>::Padding(const std::vector<uint32_t>& pads, T padding_value) {
  CHECK(!this->data_.empty());
  CHECK_EQ(pads.size(), 4);
  uint32_t pad_rows1 = pads.at(0);  // up
  uint32_t pad_rows2 = pads.at(1);  // bottom
  uint32_t pad_cols1 = pads.at(2);  // left
  uint32_t pad_cols2 = pads.at(3);  // right

  arma::Cube<T> new_data(this->data_.n_rows + pad_rows1 + pad_rows2,
                         this->data_.n_cols + pad_cols1 + pad_cols2,
                         this->data_.n_slices);
  new_data.fill(padding_value);

  new_data.subcube(pad_rows1, pad_cols1, 0, new_data.n_rows - pad_rows2 - 1,
                   new_data.n_cols - pad_cols2 - 1, new_data.n_slices - 1) =
      this->data_;
  this->data_ = std::move(new_data);
  this->raw_shapes_ =
      std::vector<uint32_t>{this->channels(), this->rows(), this->cols()};
}

template <typename T>
void Tensor<T>::Fill(T value) {
  CHECK(!this->data_.empty());
  this->data_.fill(value);
}

template <typename T>
void Tensor<T>::Fill(const std::vector<T>& values, bool row_major) {
  CHECK(!this->data_.empty());
  const uint32_t total_elems = this->data_.size();
  CHECK_EQ(values.size(), total_elems);
  if (row_major) {
    const uint32_t rows = this->rows();
    const uint32_t cols = this->cols();
    const uint32_t planes = rows * cols;
    const uint32_t channels = this->data_.n_slices;

    for (uint32_t i = 0; i < channels; ++i) {
      arma::Mat<T>& channel_data = this->data_.slice(i);
      arma::Mat<T> channel_data_t((T*)values.data() + i * planes, this->cols(),
                                  this->rows(), false, true);
      channel_data = channel_data_t.t();
    }
  } else {
    std::copy(values.begin(), values.end(), this->data_.memptr());
  }
}

template <typename T>
void Tensor<T>::Show() {
  for (uint32_t i = 0; i < this->channels(); ++i) {
    LOG(INFO) << "Channel: " << i;
    LOG(INFO) << "\n" << this->data_.slice(i);
  }
}

template <typename T>
void Tensor<T>::Flatten(bool row_major) {
  CHECK(!this->data_.empty());
  const uint32_t size = this->data_.size();
  this->Reshape({size}, row_major);
}

template <typename T>
void Tensor<T>::RandN(T mean, T var) {
  static_assert(std::is_floating_point_v<T>);
  CHECK(!this->data_.empty());
  std::random_device rd;
  std::mt19937 mt(rd());

  std::normal_distribution<T> dist(mean, var);
  for (uint32_t i = 0; i < this->size(); ++i) {
    this->index(i) = dist(mt);
  }
}

template <typename T>
void Tensor<T>::RandU(T min, T max) {
  CHECK(!this->data_.empty());
  CHECK(max >= min);
  std::random_device rd;
  std::mt19937 mt(rd());
  if constexpr (std::is_floating_point_v<T>) {
    std::uniform_real_distribution<T> dist(min, max);
    for (uint32_t i = 0; i < this->size(); ++i) {
      this->index(i) = dist(mt);
    }
  } else {
    std::uniform_int_distribution<T> dist(min, max);
    for (uint32_t i = 0; i < this->size(); ++i) {
      this->index(i) = dist(mt);
    }
  }
}

template <typename T>
void Tensor<T>::Ones() {
  CHECK(!this->data_.empty());
  this->Fill(T{1});
}

template <typename T>
void Tensor<T>::Transform(const std::function<T(T)>& filter) {
  CHECK(!this->data_.empty());
  this->data_.transform(filter);
}

template <typename T>
const std::vector<uint32_t>& Tensor<T>::raw_shapes() const {
  CHECK(!this->raw_shapes_.empty());
  CHECK_LE(this->raw_shapes_.size(), 3);
  CHECK_GE(this->raw_shapes_.size(), 1);
  return this->raw_shapes_;
}

template <typename T>
void Tensor<T>::Reshape(const std::vector<uint32_t>& shapes, bool row_major) {
  CHECK(!this->data_.empty());
  CHECK(!shapes.empty());
  const uint32_t origin_size = this->size();
  const uint32_t current_size =
      std::accumulate(shapes.begin(), shapes.end(), 1, std::multiplies());
  CHECK(shapes.size() <= 3);
  CHECK(current_size == origin_size);

  std::vector<T> values;
  if (row_major) {
    values = this->values(true);
  }
  if (shapes.size() == 3) {
    this->data_.reshape(shapes.at(1), shapes.at(2), shapes.at(0));
    this->raw_shapes_ = {shapes.at(0), shapes.at(1), shapes.at(2)};
  } else if (shapes.size() == 2) {
    this->data_.reshape(shapes.at(0), shapes.at(1), 1);
    this->raw_shapes_ = {shapes.at(0), shapes.at(1)};
  } else {
    this->data_.reshape(1, shapes.at(0), 1);
    this->raw_shapes_ = {shapes.at(0)};
  }

  if (row_major) {
    this->Fill(values, true);
  }
}

template <typename T>
T* Tensor<T>::raw_ptr() {
  CHECK(!this->data_.empty());
  return this->data_.memptr();
}

template <typename T>
T* Tensor<T>::raw_ptr(uint32_t offset) {
  const uint32_t size = this->size();
  CHECK(!this->data_.empty());
  CHECK_LT(offset, size);
  return this->data_.memptr() + offset;
}

template <typename T>
std::vector<T> Tensor<T>::values(bool row_major) {
  CHECK_EQ(this->data_.empty(), false);
  std::vector<T> values(this->data_.size());

  if (!row_major) {
    std::copy(this->data_.mem, this->data_.mem + this->data_.size(),
              values.begin());
  } else {
    uint32_t index = 0;
    for (uint32_t c = 0; c < this->data_.n_slices; ++c) {
      const arma::Mat<T>& channel = this->data_.slice(c).t();
      std::copy(channel.begin(), channel.end(), values.begin() + index);
      index += channel.size();
    }
    CHECK_EQ(index, values.size());
  }
  return values;
}

template <typename T>
T* Tensor<T>::matrix_raw_ptr(uint32_t index) {
  CHECK_LT(index, this->channels());
  uint32_t offset = index * this->rows() * this->cols();
  CHECK_LE(offset, this->size());
  T* mem_ptr = this->raw_ptr(offset);
  return mem_ptr;
}

template <typename T>
void Tensor<T>::set_data(arma::Cube<T>&& data) {
  CHECK(data.n_rows == this->data_.n_rows)
      << data.n_rows << " != " << this->data_.n_rows;
  CHECK(data.n_cols == this->data_.n_cols)
      << data.n_cols << " != " << this->data_.n_cols;
  CHECK(data.n_slices == this->data_.n_slices)
      << data.n_slices << " != " << this->data_.n_slices;
  this->data_ = std::move(data);
}

using ftensor = Tensor<float>;
using sftensor = std::shared_ptr<Tensor<float>>;

using u1tensor = Tensor<uint8_t>;
using su1tensor = std::shared_ptr<Tensor<uint8_t>>;

}  // namespace kuiper_infer

#endif  // KUIPER_INFER_DATA_BLOB_HPP_
