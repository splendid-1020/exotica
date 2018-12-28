/*
 *      Author: Vladimir Ivan
 *
 * Copyright (c) 2017, University of Edinburgh
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of  nor the names of its contributors may be used to
 *    endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "exotica_core_task_maps/eff_position.h"

REGISTER_TASKMAP_TYPE("EffPosition", exotica::EffPosition);

namespace exotica
{
EffPosition::EffPosition() = default;
EffPosition::~EffPosition() = default;

void EffPosition::Update(Eigen::VectorXdRefConst x, Eigen::VectorXdRef phi)
{
    if (phi.rows() != kinematics[0].phi.rows() * 3) ThrowNamed("Wrong size of phi!");
    for (int i = 0; i < kinematics[0].phi.rows(); i++)
    {
        phi(i * 3) = kinematics[0].phi(i).p[0];
        phi(i * 3 + 1) = kinematics[0].phi(i).p[1];
        phi(i * 3 + 2) = kinematics[0].phi(i).p[2];
    }
}

void EffPosition::Update(Eigen::VectorXdRefConst x, Eigen::VectorXdRef phi, Eigen::MatrixXdRef jacobian)
{
    if (phi.rows() != kinematics[0].phi.rows() * 3) ThrowNamed("Wrong size of phi!");
    if (jacobian.rows() != kinematics[0].jacobian.rows() * 3 || jacobian.cols() != kinematics[0].jacobian(0).data.cols()) ThrowNamed("Wrong size of jacobian! " << kinematics[0].jacobian(0).data.cols());
    for (int i = 0; i < kinematics[0].phi.rows(); i++)
    {
        phi(i * 3) = kinematics[0].phi(i).p[0];
        phi(i * 3 + 1) = kinematics[0].phi(i).p[1];
        phi(i * 3 + 2) = kinematics[0].phi(i).p[2];
        jacobian.middleRows(i * 3, 3) = kinematics[0].jacobian[i].data.topRows(3);
    }
}

int EffPosition::TaskSpaceDim()
{
    return kinematics[0].phi.rows() * 3;
}
}
