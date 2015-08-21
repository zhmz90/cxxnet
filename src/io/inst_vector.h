#ifndef CXXNET_INST_VECTOR_H_
#define CXXNET_INST_VECTOR_H_
/*!
 * \file inst_vector.h
 * \brief holder of a sequence of DataInst in CPU
 *        that are not necessarily of same shape
 */
#include "./data.h"
#include <vector>
#include <dmlc/base.h>
#include <mshadow/tensor.h>
namespace cxxnet {
/*!
 * \brief tensor vector that can store sequence of tensor
 *  in a memory compact way, tensors do not have to be of same shape
 */
template<int dim, typename DType>
class TensorVector {
 public:
  TensorVector(void) {
    this->Clear();
  }
  // get i-th tensor
  inline mshadow::Tensor<cpu, dim, DType>
  operator[](size_t i) const {
    CHECK(i + 1 < offset_.size());
    CHECK(shape_[i].Size() == offset_[i + 1] - offset_[i]);
    return mshadow::Tensor<cpu, dim, DType>
        ((DType*)BeginPtr(content_) + offset_[i], shape_[i]);
  }
  inline mshadow::Tensor<cpu, dim, DType> Back() const {
    return (*this)[Size() - 1];
  }
  inline size_t Size(void) const {
    return shape_.size();
  }
  // push a tensor of certain shape
  // return the reference of the pushed tensor
  inline void Push(mshadow::Shape<dim> shape) {
    shape_.push_back(shape);
    offset_.push_back(offset_.back() + shape.Size());
    content_.resize(offset_.back());
  }
  inline void Clear(void) {
    offset_.clear();
    offset_.push_back(0);
    content_.clear();
    shape_.clear();
  }
 private:
  // offset of the data content
  std::vector<size_t> offset_;
  // data content
  std::vector<DType> content_;
  // shape of data
  std::vector<mshadow::Shape<dim> > shape_;
};

/*!
 * \brief instance vector that can holds
 * non-uniform shape data instance in a shape efficient way
 */
class InstVector {
 public:  
  inline size_t Size(void) const {
    return index_.size();
  }
  // instance
  inline DataInst operator[](size_t i) const {
    DataInst inst;
    inst.index = index_[i];
    inst.data = data_[i];
    inst.label = label_[i];
    return inst;
  }
  // get back of instance vector
  inline DataInst Back() const {
    return (*this)[Size() - 1];
  }
  inline void Clear(void) {
    index_.clear();
    data_.Clear();
    label_.Clear();
  }
  inline void Push(unsigned index,
                   mshadow::Shape<3> dshape,
                   mshadow::Shape<1> lshape) {
    index_.push_back(index);
    data_.Push(dshape);
    label_.Push(lshape);
  }
  
 private:  
  /*! \brief index of the data */
  std::vector<unsigned> index_;
  // label
  TensorVector<3, real_t> data_;
  // data
  TensorVector<1, real_t> label_;
};
}  // cxxnet
#endif  // CXXNET_TENSOR_VECTOR_H_
