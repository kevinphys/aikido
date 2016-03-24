#ifndef AIKIDO_PERCEPTION_APRILTAGSMODULE_H
#define AIKIDO_PERCEPTION_APRILTAGSMODULE_H

#include <string>
#include <ros/ros.h>
#include <ros/forwards.h>
#include <ros/single_subscriber_publisher.h>
#include <tf/transform_listener.h>
#include "yaml-cpp/yaml.h"

#include <dart/dart.h>
#include <aikido/util/CatkinResourceRetriever.hpp>

#include "PerceptionModule.hpp"


namespace aikido{
namespace perception{

class AprilTagsModule : public virtual PerceptionModule
{
public:
	AprilTagsModule(ros::NodeHandle _node, const std::string _marker_topic, const std::string _marker_data_path,
					const dart::common::ResourceRetrieverPtr& _delegate, const std::string _urdf_path, 
					const std::string _destination_frame, dart::dynamics::BodyNode* _reference_link);
	~AprilTagsModule()
	{
	}

	void detectObjects(std::vector<dart::dynamics::SkeletonPtr>& skeleton_list,double timeout=10.0) override; 


private:
	//Member variables
	std::string marker_topic;
	std::string marker_data_path;
	std::string urdf_path;
	std::string destination_frame;
	dart::common::ResourceRetrieverPtr delegate;
	dart::dynamics::BodyNode* reference_link;

	tf::TransformListener listener;

	ros::NodeHandle node_;
	YAML::Node tag_data;

	void getTagNameOffset(std::string tag_name, std::string& body_name, Eigen::Matrix4d& body_offset);

};

} //namespace perception
} //namespace aikido

#endif //AIKIDO_PERCEPTION_APRILTAGSMODULE_H