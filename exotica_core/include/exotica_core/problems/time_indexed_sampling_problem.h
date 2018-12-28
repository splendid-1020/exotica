/*
 *      Author: Yiming Yang
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

#ifndef TIME_INDEXED_SAMPLING_PROBLEM_H_
#define TIME_INDEXED_SAMPLING_PROBLEM_H_

#include <exotica_core/planning_problem.h>
#include <exotica_core/tasks.h>

#include <exotica_core/time_indexed_sampling_problem_initializer.h>

namespace exotica
{
class TimeIndexedSamplingProblem : public PlanningProblem, public Instantiable<TimeIndexedSamplingProblemInitializer>
{
public:
    TimeIndexedSamplingProblem();
    virtual ~TimeIndexedSamplingProblem();

    virtual void Instantiate(TimeIndexedSamplingProblemInitializer& init);

    void Update(Eigen::VectorXdRefConst x, const double& t);
    bool IsValid(Eigen::VectorXdRefConst x, const double& t); // Not overriding on purpose
    void PreUpdate() override;

    int GetSpaceDim();

    void SetGoalEQ(const std::string& task_name, Eigen::VectorXdRefConst goal);
    Eigen::VectorXd GetGoalEQ(const std::string& task_name);
    void SetRhoEQ(const std::string& task_name, const double& rho);
    double GetRhoEQ(const std::string& task_name);

    void SetGoalNEQ(const std::string& task_name, Eigen::VectorXdRefConst goal);
    Eigen::VectorXd GetGoalNEQ(const std::string& task_name);
    void SetRhoNEQ(const std::string& task_name, const double& rho);
    double GetRhoNEQ(const std::string& task_name);

    std::vector<double> GetBounds();

    Eigen::VectorXd GetGoalState();
    double GetGoalTime();
    void SetGoalState(Eigen::VectorXdRefConst qT);
    void SetGoalTime(const double& t);

    Eigen::VectorXd vel_limits;
    TaskSpaceVector phi;
    SamplingTask inequality;
    SamplingTask equality;
    TimeIndexedSamplingProblemInitializer parameters;
    TaskSpaceVector constraint_phi;

    int length_phi;
    int length_jacobian;
    int num_tasks;

private:
    double T_;
    double t_goal_;
    Eigen::VectorXd goal_;
};

typedef std::shared_ptr<exotica::TimeIndexedSamplingProblem> TimeIndexedSamplingProblem_ptr;
}

#endif
