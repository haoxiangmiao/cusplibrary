/*
 *  Copyright 2008-2009 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <cusp/detail/dispatch/multiply.h>

#include <cusp/linear_operator.h>
#include <thrust/detail/type_traits.h>

namespace cusp
{
namespace detail
{

template <typename LinearOperator,
          typename MatrixOrVector1,
          typename MatrixOrVector2>
void multiply(LinearOperator&  A,
              MatrixOrVector1& B,
              MatrixOrVector2& C,
              cusp::detail::unknown_format_tag)
{
    // invoke linear_operator multiplication method
    A(B,C);
}

template <typename LinearOperator,
          typename MatrixOrVector1,
          typename MatrixOrVector2>
void multiply(LinearOperator&  A,
              MatrixOrVector1& B,
              MatrixOrVector2& C,
              cusp::detail::known_format_tag)
{
    cusp::detail::dispatch::multiply
        (A, B, C,
         typename LinearOperator::memory_space(),
         typename MatrixOrVector1::memory_space(),
         typename MatrixOrVector2::memory_space());
}

} // end namespace detail

template <typename LinearOperator,
          typename MatrixOrVector1,
          typename MatrixOrVector2>
void multiply(LinearOperator&  A,
              MatrixOrVector1& B,
              MatrixOrVector2& C)
{
    // TODO check that dimensions are compatible

    typedef typename LinearOperator::value_type   ValueType;
    typedef typename LinearOperator::memory_space MemorySpace;

    cusp::detail::multiply(A, B, C,
            typename cusp::detail::matrix_format<LinearOperator>::type());
}

} // end namespace cusp

