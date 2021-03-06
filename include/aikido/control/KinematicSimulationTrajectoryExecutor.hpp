#ifndef AIKIDO_CONTROL_KINEMATICSIMULATIONTRAJECTORYEXECUTOR_HPP_
#define AIKIDO_CONTROL_KINEMATICSIMULATIONTRAJECTORYEXECUTOR_HPP_

#include <future>
#include <mutex>

#include <aikido/control/TrajectoryExecutor.hpp>
#include <aikido/statespace/dart/MetaSkeletonStateSpace.hpp>
#include <aikido/trajectory/Trajectory.hpp>

namespace aikido {
namespace control {

/// Executes trajectories in DART. This will spin a new thread
/// and simulate trajectories by setting dof positions
/// without running dynamic simulation.
class KinematicSimulationTrajectoryExecutor : public TrajectoryExecutor
{
public:
  /// Constructor.
  /// \param skeleton Skeleton to execute trajectories on.
  ///        All trajectories must have dofs only in this skeleton.
  explicit KinematicSimulationTrajectoryExecutor(
      ::dart::dynamics::SkeletonPtr skeleton);

  virtual ~KinematicSimulationTrajectoryExecutor();

  // Documentation inherited.
  void validate(trajectory::TrajectoryPtr traj) override;

  /// Execute traj and set future upon completion.
  /// \param traj Trajectory to be executed. Its StateSpace should be a
  ///        MetaStateSpace over MetaSkeleton, and the dofs in the metaskeleton
  ///        should be all in skeleton passed to the constructor.
  /// \return future<void> for trajectory execution. If trajectory terminates
  ///        before completion, future will be set to a runtime_error.
  /// \throws invalid_argument if traj is invalid.
  std::future<void> execute(trajectory::TrajectoryPtr traj) override;

  /// \copydoc PositionCommandExecutor::step()
  ///
  /// If multiple threads are accessing this function or the skeleton associated
  /// with this executor, it is necessary to lock the skeleton before
  /// calling this method.
  void step() override;

  /// Aborts the current trajectory.
  void abort() override;

private:
  ::dart::dynamics::SkeletonPtr mSkeleton;

  bool mInProgress;
  std::unique_ptr<std::promise<void>> mPromise;
  trajectory::TrajectoryPtr mTraj;

  std::chrono::system_clock::time_point mExecutionStartTime;

  /// Manages access on mInProgress, mPromise, mTraj
  std::mutex mMutex;
};

} // namespace control
} // namespace aikido

#endif
