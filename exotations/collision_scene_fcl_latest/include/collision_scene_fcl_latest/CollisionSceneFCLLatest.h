/*
 *      Author: Vladimir Ivan
 *
 * Copyright (c) 2017, University Of Edinburgh
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

#ifndef CollisionSceneFCLLatest_H
#define CollisionSceneFCLLatest_H

#include <exotica/CollisionScene.h>
#include <fcl/fcl.h>
#include <geometric_shapes/mesh_operations.h>
#include <geometric_shapes/shape_operations.h>

namespace exotica
{
class CollisionSceneFCLLatest : public CollisionScene
{
public:

    struct CollisionData
    {
        CollisionData(CollisionSceneFCLLatest* scene) : Scene(scene), Self(true) {}

        fcl::CollisionRequestd Request;
        fcl::CollisionResultd Result;
        CollisionSceneFCLLatest* Scene;
        bool Self;
    };

    struct DistanceData
    {
        DistanceData(CollisionSceneFCLLatest* scene) : Scene(scene), Self(true), Distance{1e300} {}

        fcl::DistanceRequestd Request;
        fcl::DistanceResultd Result;
        CollisionSceneFCLLatest* Scene;
        std::vector<CollisionProxy> Proxies;
        double Distance;
        bool Self;
    };

    CollisionSceneFCLLatest();

    /**
       * \brief Destructor
       */
    virtual ~CollisionSceneFCLLatest();

    static bool isAllowedToCollide(fcl::CollisionObjectd* o1, fcl::CollisionObjectd* o2, bool self, CollisionSceneFCLLatest* scene);
    static bool collisionCallback(fcl::CollisionObjectd* o1, fcl::CollisionObjectd* o2, void* data);
    static bool collisionCallbackDistance(fcl::CollisionObjectd* o1, fcl::CollisionObjectd* o2, void* data, double& dist);

    /**
       * \brief Check if the whole robot is valid (collision only).
       * @param self Indicate if self collision check is required.
       * @return True, if the state is collision free..
       */
    virtual bool isStateValid(bool self = true);
    virtual bool isCollisionFree(const std::string& o1, const std::string& o2);

    ///
    /// \brief Computes collision distances.
    /// \param self Indicate if self collision check is required.
    /// \param computePenetrationDepth If set to true, accurate penetration depth is computed.
    /// \return Collision proximity objectects for all colliding pairs of objects.
    ///
    virtual std::vector<CollisionProxy> getCollisionDistance(bool self);
    virtual std::vector<CollisionProxy> getCollisionDistance(const std::string& o1, const std::string& o2);

    /**
       * @brief      Gets the collision world links.
       *
       * @return     The collision world links.
       */
    virtual std::vector<std::string> getCollisionWorldLinks();

    /**
       * @brief      Gets the collision robot links.
       *
       * @return     The collision robot links.
       */
    virtual std::vector<std::string> getCollisionRobotLinks();

    virtual Eigen::Vector3d getTranslation(const std::string & name);

    ///
    /// \brief Creates the collision scene from kinematic elements.
    /// \param objects Vector kinematic element pointers of collision objects.
    ///
    virtual void updateCollisionObjects(const std::map<std::string, std::shared_ptr<KinematicElement>>& objects);

    ///
    /// \brief Updates collision object transformations from the kinematic tree.
    ///
    virtual void updateCollisionObjectTransforms();

private:

    static std::shared_ptr<fcl::CollisionObjectd> constructFclCollisionObject(std::shared_ptr<KinematicElement> element);
    static void checkCollision(fcl::CollisionObjectd* o1, fcl::CollisionObjectd* o2, CollisionData* data);
    static void computeDistance(fcl::CollisionObjectd* o1, fcl::CollisionObjectd* o2, DistanceData* data);

    std::map<std::string, std::shared_ptr<fcl::CollisionObjectd>> fcl_cache_;

    std::vector<fcl::CollisionObjectd*> fcl_objects_;
};

typedef std::shared_ptr<CollisionSceneFCLLatest> CollisionSceneFCLLatest_ptr;
}

#endif // CollisionSceneFCLLatest_H