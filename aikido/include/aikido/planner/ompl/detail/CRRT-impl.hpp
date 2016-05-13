namespace aikido {
namespace planner {
namespace ompl {

//=============================================================================
template <template <typename T> class NN> 
void CRRT::setNearestNeighbors() 
{
  mNN.reset(new NN<Motion *>());
}


} // namespace ompl
} // namespace planner
} // namespace aikido
