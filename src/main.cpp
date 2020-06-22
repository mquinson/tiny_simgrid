#include "unfolding/UnfoldingChecker.h"
#include "unfolding/state.h"
#include "unfolding/transition.h"
#include "unfolding/configuration.h"
#include "unfolding/EventSet.h"
#include "unfolding/UnfoldingEvent.h"
#include "app/actor.h"
#include "app/mailbox.h"

using namespace std;

static int nbInt = 0;
void exhautiveExplore(std::list<State> stateStack, std::list<Transition> transList)
{
  State s                        = stateStack.back();
  std::set<Transition> trans_set = s.getEnabledTransition();
  if (trans_set.empty()) {
    nbInt++;
    std::cout << " \n Interleaving  " << nbInt << ":  ";
    for (auto t : transList)
      std::cout << "(t_" << t.id << ",p_" << t.actor_id << "-" << t.type << " )   ";

    stateStack.pop_back();
  } else {
    for (auto t : trans_set) {
      std::list<Transition> transList1 = transList;
      transList1.push_back(t);

      State s1 = s.execute(t);
      stateStack.push_back(s1);
      exhautiveExplore(stateStack, transList1);
    }
  }
}
bool test_reduction(std::set<Actor> actors, std::set<Mailbox> mailboxes, std::vector<unsigned int> confs,
                    unsigned int evt_count)
{
  UnfoldingChecker UC(confs, evt_count);

  UC.explore(new State(actors.size(), actors, mailboxes));

  if (UC.error_count() > 0) {
    std::cerr << "\n\nSOMETHING WENT WRONG. Error count: " << UC.error_count() << "\n";
    exit(EXIT_FAILURE);
  } else {
    return true;
  }
}

int main(int argc, char** argv)
{
  clock_t begin = clock();
  nb_events     = 0;
  UnfoldingChecker UC;
  mc::EventSet A, D;
  mc::EventSet prev_exC;
  mc::Configuration C;
  State* initState;
  std::set<Actor> actor_set;
  std::set<Mailbox> mailboxes;
  std::list<State> stateStack;
  std::list<Transition> transList;

  // keep history of maximal event when exploring C
  std::list<set<int>> maxEventHis;

  int example = 1;
  std::cout << " enter example:";
  if (argc == 2)
    example = std::atoi(argv[1]);
  else
    std::cin >> example;

  switch (example) {
    case 1: { // the first example (in the paper)
              // Transition(read_write, access_variable)

      test_reduction(
          {
              Actor(0, {Transition(1, 0)}), // write x
              Actor(1, {Transition(0, 0)}), // read x
              Actor(2, {Transition(0, 0)})  // read x
          },
          {/* no mailbox */}, {3, 3, 3, 3}, 20);
    } break;

    case 2: { // the second example
      test_reduction(
          {
              Actor(1, {Transition(1, 0)}), // P0: write X
              Actor(2, {Transition(1, 1),   // P1: write Y
                        Transition(1, 0)})  // P1: write X
          },
          {/* no mailbox */}, {3, 3}, 10);
    } break;

    case 3: { // the third example - 1 trace
      // Transition(read_write, access_variable)
      test_reduction(
          {
              Actor(0, {Transition(1, 0)}), // P0: write X
              Actor(1, {Transition(1, 1)}), // P1: write Y
              Actor(2, {Transition(1, 2)})  // P2: write Z
          },
          {/* no mailbox */}, {3}, 3);
    } break;

    case 4: { // the fourth example - 6 traces

      // Transition(read_write, access_variable)
      test_reduction({Actor(0, {Transition(1, 0)}), Actor(1, {Transition(1, 0)}), Actor(2, {Transition(1, 0)})},
                     {/* no mailbox */}, {3, 3, 3, 3, 3, 3}, 27);
    } break;

    case 5: { // the fifth example - 4 traces

      // Transition(read_write, access_variable)
      test_reduction({Actor(0, {Transition(1, 0), Transition(1, 1)}), Actor(1, {Transition(1, 0), Transition(1, 1)})},
                     {/* no mailbox */}, {4, 4, 4, 4}, 16);

    } break;

    case 6: { // 6th example - 3 traces

      // Transition(read_write, access_variable)
      test_reduction({Actor(0, {Transition(1, 0), Transition(1, 1)}), Actor(1, {Transition(1, 1), Transition(1, 0)})},
                     {/* no mailbox */}, {4, 4, 4}, 16);
    } break;

    case 7: { // 7th example - 4 traces

      // Transition(read_write, access_variable)
      test_reduction(
          {Actor(0, {Transition(1, 0)}), Actor(1, {Transition(1, 1)}), Actor(2, {Transition(1, 1), Transition(1, 0)})},
          {/* no mailbox */}, {4, 4, 4, 4}, 27);

    } break;

    case 8: { // mutex example - 1 traces
              // Transition(read_write, access_variable)
      test_reduction({Actor(0, {Transition(2, 0), Transition(3, 0)}), Actor(1, {Transition(2, 0), Transition(3, 0)})},
                     {/* no mailbox */}, {2}, 2);
    } break;

    case 9: { // mutex example - 1 trace
              // Transition(read_write, access_variable)
      test_reduction({Actor(0, {Transition(0, 0), Transition(2, 1), Transition(3, 1)}),
                      Actor(1, {Transition(2, 1), Transition(3, 1)})},
                     {/* no mailbox */}, {2}, 2);
    } break;

    case 10: { // 3 traces

      // Transition(read_write, access_variable)
      test_reduction({Actor(0, {Transition(1, 0), Transition(1, 0)}), Actor(1, {Transition(1, 1), Transition(1, 0)})},
                     {/* no mailbox */}, {4, 4, 4}, 18);

    } break;

    case 11: { // the first simix model -> 2 traces
               // Transition (maiboxid, commid, type)
      test_reduction({Actor(0, {Transition(1, 1, "Isend"), Transition(1, 1, "Wait")}),
                      Actor(1, {Transition(1, 1, "Isend")}), Actor(2, {Transition(1, 1, "Ireceive")})},
                     {Mailbox(1)}, {4, 3}, 9);

      std::cout << "\n explore full state space :\n";
      State initState1(3, actor_set, {Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);

    } break;

    case 12: { // the 2nd simix model -> 1 trace

      // Transition (maiboxid, commid, type)
      test_reduction({Actor(0, {Transition(1, 1, "Isend"), Transition(1, 1, "Wait")}),
                      Actor(1, {Transition(2, 1, "Isend")}), Actor(2, {Transition(1, 1, "Ireceive")})},
                     {Mailbox(1)}, {4}, 4);

      std::cout << "\n explore full state space :\n";
      State initState1(3, actor_set, {Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);
    } break;

    case 13: { // the first simix model -> 2 traces
               // Transition (maiboxid, commid, type)
      test_reduction({Actor(0, {Transition(1, 1, "Isend"), Transition(1, 1, "Wait")}),
                      Actor(1, {Transition(1, 1, "Isend"), Transition(1, 1, "Wait")}),
                      Actor(2, {Transition(1, 1, "Ireceive"), Transition(1, 1, "Wait")})},
                     {Mailbox(1)}, {5, 5}, 13);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);

    } break;

    case 14: { // the first simix model -> 2 traces

      // Transition (maiboxid, commid, type)
      test_reduction({Actor(0, {Transition(1, 1, "Isend"), Transition(1, 1, "Wait")}),
                      Actor(1, {Transition(1, 1, "Isend"), Transition(1, 1, "Wait")}),
                      Actor(2, {Transition(1, 1, "Ireceive"), Transition(1, 1, "Wait"), Transition(1, 1, "Ireceive"),
                                Transition(1, 1, "Wait")})},
                     {Mailbox(1)}, {8, 8}, 22);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);
    } break;

    case 15: { // the first simix model -> 6 traces
               // Transition (maiboxid, commid, type)
      test_reduction({Actor(0, {Transition(1, 1, "Isend"), Transition(1, 1, "Wait")}),
                      Actor(1, {Transition(1, 1, "Isend"), Transition(1, 1, "Wait")}),

                      Actor(2, {Transition(1, 1, "Ireceive"), Transition(1, 1, "Wait"), Transition(1, 2, "Ireceive"),
                                Transition(1, 2, "Wait")}),

                      Actor(3, {Transition(1, 1, "Isend"), Transition(1, 1, "Wait")})},
                     {Mailbox(1)}, {9, 9, 9, 9, 9, 9}, 59);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);
    } break;

    case 16: { // the first simix model -> 6 traces

      // Transition (maiboxid, commid, type)
      test_reduction({Actor(0, {Transition(1, 1, "Ireceive"), Transition(1, 1, "Wait"), Transition(1, 2, "Ireceive"),
                                Transition(1, 2, "Wait"), Transition(1, 3, "Ireceive"), Transition(1, 3, "Wait")}),

                      Actor(1, {Transition(1, 1, "Isend"), Transition(1, 1, "Wait")}),
                      Actor(2, {Transition(1, 1, "Isend"), Transition(1, 1, "Wait")}),
                      Actor(3, {Transition(1, 1, "Isend"), Transition(1, 1, "Wait")})},
                     {Mailbox(1)}, {12, 12, 12, 12, 12, 12}, 90);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);

    } break;

    case 17: { //  3 traces

      // Transition (maiboxid, commid, type)
      test_reduction({Actor(0, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}),
                      Actor(1, {Transition(1, 1, "Isend")}), Actor(2, {Transition(1, 1, "Ireceive")})},
                     {Mailbox(1)}, {4, 4, 4}, 14);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);

    } break;

    case 18: { // 162 traces
               // Transition (maiboxid, commid, type)
      std::vector<unsigned int> expected;
      for (int i = 0; i < 162; i++)
        expected.push_back(12);
      test_reduction(
          {
              Actor(0, {Transition(1, 1, "Ireceive"), Transition(1, 1, "Test"), Transition(1, 2, "Ireceive"),
                        Transition(1, 2, "Test"), Transition(1, 3, "Ireceive"), Transition(1, 3, "Test")}),

              Actor(1, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}),
              Actor(2, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}),
              Actor(3, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}),
          },
          {Mailbox(1)}, expected, 1299);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);
    } break;

    case 19: { // 6 traces

      // Transition (maiboxid, commid, type)
      actor_set.insert(Actor(0, {Transition(1, 2, "Ireceive"), Transition(1, 2, "Test")}));
      actor_set.insert(Actor(1, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}));
      actor_set.insert(Actor(2, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}));

      initState         = new State(3, actor_set, {Mailbox(1)});
      UnfoldingEvent* e = new UnfoldingEvent(initState);
      UC.explore(C, {mc::EventSet()}, D, A, e, prev_exC, actor_set);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);

    } break;

    case 20: { // 18 traces
               // Transition (maiboxid, commid, type)
      actor_set.insert(Actor(0, {Transition(1, 1, "Ireceive"), Transition(1, 1, "Test"), Transition(1, 2, "Ireceive"),
                                 Transition(1, 2, "Test")}));
      actor_set.insert(Actor(1, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}));
      actor_set.insert(Actor(2, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}));

      initState = new State(3, actor_set, {Mailbox(1)});

      UnfoldingEvent* e = new UnfoldingEvent(initState);
      UC.explore(C, {mc::EventSet()}, D, A, e, prev_exC, actor_set);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);
    } break;

    case 21: { // 54 traces

      // Transition (maiboxid, commid, type)
      actor_set.insert(Actor(0, {Transition(1, 1, "Ireceive"), Transition(1, 1, "Test"), Transition(1, 2, "Ireceive"),
                                 Transition(1, 2, "Test")}));
      actor_set.insert(Actor(1, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}));
      actor_set.insert(Actor(2, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}));
      actor_set.insert(Actor(3, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}));

      initState = new State(4, actor_set, {Mailbox(1)});

      UnfoldingEvent* e = new UnfoldingEvent(initState);
      UC.explore(C, {mc::EventSet()}, D, A, e, prev_exC, actor_set);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);

    } break;

    case 22: {

      // Transition (maiboxid, commid, type)
      actor_set.insert(Actor(0, {Transition(1, 1, "Ireceive"), Transition(1, 1, "Test"), Transition(1, 2, "Ireceive"),
                                 Transition(1, 2, "Test"), Transition(1, 3, "Ireceive"), Transition(1, 3, "Test"),
                                 Transition(1, 3, "Ireceive"), Transition(1, 3, "Test")}));
      actor_set.insert(Actor(1, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}));
      actor_set.insert(Actor(2, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}));
      actor_set.insert(Actor(3, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}));
      actor_set.insert(Actor(4, {Transition(1, 1, "localComp"), Transition(1, 1, "Isend"), Transition(1, 1, "Test")}));

      initState = new State(5, actor_set, {Mailbox(1)});

      UnfoldingEvent* e = new UnfoldingEvent(initState);
      UC.explore(C, {mc::EventSet()}, D, A, e, prev_exC, actor_set);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);

    } break;

    case 23: { // 18 traces
      // Transition (maiboxid, commid, type)
      actor_set.insert(Actor(0, {Transition(1, 1, "Ireceive"), Transition(1, 1, "Test")}));
      actor_set.insert(Actor(1, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}));
      actor_set.insert(Actor(2, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}));
      actor_set.insert(Actor(3, {Transition(1, 1, "Isend"), Transition(1, 1, "Test")}));

      initState = new State(4, actor_set, {Mailbox(1)});

      UnfoldingEvent* e = new UnfoldingEvent(initState);
      UC.explore(C, {mc::EventSet()}, D, A, e, prev_exC, actor_set);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);

    } break;

    case 24: { // 8 traces

      // transition (maiboxid, commid, type)
      actor_set.insert(Actor(0, {Transition(1, 1, "Ireceive")}));
      actor_set.insert(Actor(1, {Transition(1, 2, "Ireceive"), Transition(1, 2, "Test")}));
      actor_set.insert(Actor(2, {Transition(1, 3, "Isend")}));
      actor_set.insert(Actor(3, {Transition(1, 4, "localComp"), Transition(1, 4, "Isend")}));

      initState         = new State(4, actor_set, {Mailbox(1)});
      UnfoldingEvent* e = new UnfoldingEvent(initState);
      UC.explore(C, {mc::EventSet()}, D, A, e, prev_exC, actor_set);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);
    } break;

    case 25: { //  master- slaver 4 nodes
      // master node
      actor_set.insert(Actor(0, {Transition(2, 1, "Isend"), Transition(3, 2, "Isend"), Transition(4, 3, "Isend"),
                                 Transition(2, 1, "Wait"), Transition(3, 2, "Wait"), Transition(4, 3, "Wait"),
                                 Transition(1, 4, "Ireceive"), Transition(1, 4, "Wait"), Transition(1, 5, "Ireceive"),
                                 Transition(1, 5, "Wait"), Transition(1, 6, "Ireceive"), Transition(1, 6, "Wait")}));
      // client 1
      actor_set.insert(Actor(1, {Transition(2, 1, "Ireceive"), Transition(2, 1, "Wait"), Transition(0, 0, "localComp"),
                                 Transition(1, 2, "Isend"), Transition(1, 2, "Wait")}));
      // client 2
      actor_set.insert(Actor(2, {Transition(3, 1, "Ireceive"), Transition(3, 1, "Wait"), Transition(0, 0, "localComp"),
                                 Transition(1, 2, "Isend"), Transition(1, 2, "Wait")}));
      // client 3
      actor_set.insert(Actor(3, {Transition(4, 1, "Ireceive"), Transition(4, 1, "Wait"), Transition(0, 0, "localComp"),
                                 Transition(1, 2, "Isend"), Transition(1, 2, "Wait")}));

      initState = new State(4, actor_set, {Mailbox(1), Mailbox(2), Mailbox(3), Mailbox(4)});

      UnfoldingEvent* e = new UnfoldingEvent(initState);
      UC.explore(C, {mc::EventSet()}, D, A, e, prev_exC, actor_set);

      std::cout << "\n explore full state space :\n";

      State initState1(4, actor_set, {Mailbox(0), Mailbox(1), Mailbox(2)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);
    } break;

    case 26: { //  master- slaver 3 nodes

      // master node
      // Transition (maiboxid, commid, type)

      actor_set.insert(Actor(0, {Transition(2, 1, "Isend"), Transition(3, 2, "Isend"), Transition(2, 1, "Wait"),
                                 Transition(3, 2, "Wait"), Transition(1, 3, "Ireceive"), Transition(1, 3, "Wait"),
                                 Transition(1, 4, "Ireceive"), Transition(1, 4, "Wait")}));
      // client 1
      actor_set.insert(Actor(1, {Transition(2, 1, "Ireceive"), Transition(2, 1, "Wait"), Transition(0, 0, "localComp"),
                                 Transition(1, 2, "Isend"), Transition(1, 2, "Wait")}));
      // client 2
      actor_set.insert(Actor(2, {Transition(3, 1, "Ireceive"), Transition(3, 1, "Wait"), Transition(0, 0, "localComp"),
                                 Transition(1, 2, "Isend"), Transition(1, 2, "Wait")}));

      initState = new State(3, actor_set, {Mailbox(1), Mailbox(2), Mailbox(3)});

      UnfoldingEvent* e = new UnfoldingEvent(initState);
      UC.explore(C, {mc::EventSet()}, D, A, e, prev_exC, actor_set);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(1), Mailbox(2), Mailbox(3)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);

    } break;
    case 28: { // dtg benchmark

      // Transition (maiboxid, commid, type)

      // node 0
      actor_set.insert(Actor(0, {Transition(1, 1, "Ireceive"), Transition(1, 1, "Wait"), Transition(5, 2, "Isend"),
                                 Transition(5, 2, "Wait"), Transition(1, 3, "Ireceive"), Transition(1, 3, "Wait")}));
      // node 1
      actor_set.insert(Actor(1, {Transition(1, 1, "Isend"), Transition(1, 1, "Wait"), Transition(4, 2, "Isend"),
                                 Transition(4, 2, "Wait")}));

      // node 2
      actor_set.insert(Actor(2, {Transition(3, 1, "Ireceive"), Transition(3, 1, "Wait"), Transition(1, 2, "Isend"),
                                 Transition(1, 2, "Wait")}));
      // node 3
      actor_set.insert(Actor(3, {Transition(4, 1, "Ireceive"), Transition(4, 1, "Wait"), Transition(5, 2, "Ireceive"),
                                 Transition(5, 2, "Wait")}));
      // node 4
      actor_set.insert(Actor(4, {Transition(3, 1, "Isend"), Transition(3, 1, "Wait")}));

      initState         = new State(5, actor_set, {Mailbox(1), Mailbox(2), Mailbox(3), Mailbox(4), Mailbox(5)});
      UnfoldingEvent* e = new UnfoldingEvent(initState);
      UC.explore(C, {mc::EventSet()}, D, A, e, prev_exC, actor_set);

      std::cout << "\n explore full state space :\n";
      State initState1(5, actor_set, {Mailbox(1), Mailbox(2), Mailbox(3), Mailbox(4), Mailbox(5)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack,transList);

    } break;

    case 29: { /*		complex-deadlock
if (nprocs < 3)
{
  printf ("not enough tasks\n");
}
else if (rank == 0)
{
  memset (buf0, 0, buf_size);

  zero_to_two = 1;

  MPI_Send (&zero_to_two, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);

  MPI_Recv (buf1, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);

  MPI_Send (buf0, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD);
}
else if (rank == 1)
{
  memset (buf1, 1, buf_size);

  MPI_Recv (buf0, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

  MPI_Send (buf1, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
}
else if (rank == 2)
{

  MPI_Recv (&zero_to_two, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
} */

      // Transition (maiboxid, commid, type)

      // node 0
      actor_set.insert(Actor(0, {Transition(2, 1, "Isend"), Transition(2, 1, "Wait"), Transition(0, 2, "Ireceive"),
                                 Transition(0, 2, "Wait"), Transition(1, 3, "Isend"), Transition(1, 3, "Wait")}));
      // node 1
      actor_set.insert(Actor(1, {Transition(1, 1, "Ireceive"), Transition(1, 1, "Wait"), Transition(0, 2, "Isend"),
                                 Transition(0, 2, "Wait")}));

      // node 2
      actor_set.insert(Actor(2, {Transition(2, 1, "Ireceive"), Transition(2, 1, "Wait")}));

      initState = new State(3, actor_set, {Mailbox(0), Mailbox(1), Mailbox(2)});

      UnfoldingEvent* e = new UnfoldingEvent(initState);
      UC.explore(C, {mc::EventSet()}, D, A, e, prev_exC, actor_set);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(0), Mailbox(1), Mailbox(2)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack,transList);

    } break;

    case 30: { /*		wait-deadlock
     if (nprocs < 2)
     {
     printf ("not enough tasks\n");
     }
     else if (rank == 0)
     {
     memset (buf0, 0, buf_size);

     MPI_Irecv (buf1, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD, &req);

     MPI_Wait (&req, &status);

     MPI_Send (buf0, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD);
     }
     else if (rank == 1)
     {
     memset (buf1, 1, buf_size);

     MPI_Irecv (buf0, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &req);

     MPI_Wait (&req, &status);

     MPI_Send (buf1, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
     }
     */
               // Transition (maiboxid, commid, type)

      // node 0
      actor_set.insert(Actor(0, {Transition(0, 1, "Ireceive"), Transition(0, 1, "Wait"), Transition(1, 2, "Isend"),
                                 Transition(1, 2, "Wait")}));
      // node 1
      actor_set.insert(Actor(1, {Transition(1, 1, "Ireceive"), Transition(1, 1, "Wait"), Transition(0, 2, "Isend"),
                                 Transition(0, 2, "Wait")}));

      initState = new State(2, actor_set, {Mailbox(0), Mailbox(1)});
      std::cout << "\n UDPOR state space :\n";

      UnfoldingEvent* e = new UnfoldingEvent(initState);
      UC.explore(C, {mc::EventSet()}, D, A, e, prev_exC, actor_set);

      std::cout << "\n explore full state space :\n";
      State initState1(2, actor_set, {Mailbox(0), Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack,transList);

    } break;

    case 31: { /*		waitall-deadlock
     if (nprocs < 3)
     {
     printf ("not enough tasks\n");
     }
     else if (rank == 0)
     {
     MPI_Irecv (buf0, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD, &reqs[0]);

     MPI_Irecv (buf1, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD, &reqs[1]);

     MPI_Waitall (2, reqs, statuses);

     MPI_Send (buf1, buf_size, MPI_INT, 1, 1, MPI_COMM_WORLD);
     }
     else if (rank == 1)
     {
     memset (buf0, 0, buf_size);

     MPI_Isend (buf0, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &reqs[0]);

     MPI_Isend (buf0, buf_size, MPI_INT, 2, 1, MPI_COMM_WORLD, &reqs[1]);

     MPI_Waitall (2, reqs, statuses);

     MPI_Recv (buf1, buf_size, MPI_INT, 0, 1, MPI_COMM_WORLD, statuses);

     MPI_Send (buf0, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
     }
     else if (rank == 2)
     {
     MPI_Recv (buf1, buf_size, MPI_INT, 1, 1, MPI_COMM_WORLD, statuses);
     }
     */
      // Transition (maiboxid, commid, type)

      // node 0
      actor_set.insert(Actor(0, {Transition(0, 1, "Ireceive"), Transition(0, 2, "Ireceive"), Transition(0, 1, "Wait"),
                                 Transition(0, 2, "Wait"), Transition(1, 3, "Isend"), Transition(1, 3, "Wait")}));
      // node 1
      actor_set.insert(Actor(1, {Transition(0, 1, "Isend"), Transition(2, 2, "Isend"), Transition(0, 1, "Wait"),
                                 Transition(2, 2, "Wait"), Transition(1, 3, "Ireceive"), Transition(1, 3, "Wait"),
                                 Transition(0, 4, "Isend"), Transition(0, 4, "Wait")}));

      // node 2
      actor_set.insert(Actor(2, {Transition(2, 1, "Ireceive"), Transition(2, 1, "Wait")}));

      initState = new State(3, actor_set, {Mailbox(0), Mailbox(1), Mailbox(2)});

      UnfoldingEvent* e = new UnfoldingEvent(initState);
      UC.explore(C, {mc::EventSet()}, D, A, e, prev_exC, actor_set);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(0), Mailbox(1), Mailbox(2)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack,transList);
    } break;
    case 32: { /*		no-error-wait-any_src
     if (nprocs < 2)
     {
     printf ("not enough tasks\n");
     }
     else if (rank == 0)
     {
     memset (buf0, 0, buf_size);
     MPI_Irecv (buf1, buf_size, MPI_INT,  MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &req);

     MPI_Send (buf0, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD);

     MPI_Wait (&req, &status);
     }
     else if (rank == 1)
     {
     memset (buf1, 1, buf_size);

     MPI_Irecv (buf0, buf_size, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &req);

     MPI_Wait (&req, &status);

     MPI_Send (buf1, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
     }

*/

      // Transition (maiboxid, commid, type)

      // node 0
      actor_set.insert(Actor(0, {Transition(0, 1, "Ireceive"), Transition(1, 2, "Isend"), Transition(1, 2, "Wait"),
                                 Transition(0, 1, "Wait")}));
      // node 1
      actor_set.insert(Actor(1, {Transition(1, 1, "Ireceive"), Transition(1, 1, "Wait"), Transition(0, 2, "Isend"),
                                 Transition(0, 2, "Wait")}));

      initState = new State(2, actor_set, {Mailbox(0), Mailbox(1)});

      std::cout << "\n UDPOR state space :\n";

      UnfoldingEvent* e = new UnfoldingEvent(initState);
      UC.explore(C, {mc::EventSet()}, D, A, e, prev_exC, actor_set);

      std::cout << "\n explore full state space :\n";

      State initState1(2, actor_set, {Mailbox(0), Mailbox(1)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack, transList);
    } break;

    case 33: { /*any_src-can-deadlock3.c
            if (nprocs < 3)
        {
          printf ("not enough tasks\n");
        }
      else if (rank == 0)
        {
          MPI_Recv (buf1, buf_size, MPI_INT,
                    MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

          MPI_Send (buf1, buf_size, MPI_INT, 1, 0, MPI_COMM_WORLD);

          MPI_Recv (buf0, buf_size, MPI_INT,
                    MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        }
      else if (rank == 1)
        {
          memset (buf0, 0, buf_size);

          MPI_Send (buf0, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD);

          MPI_Recv (buf1, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        }
      else if (rank == 2)
        {
          memset (buf1, 1, buf_size);

          //sleep (60);

          MPI_Send (buf1, buf_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }

             */
      // Transition (maiboxid, commid, type)

      // node 0
      actor_set.insert(Actor(0, {Transition(0, 1, "Ireceive"), Transition(0, 1, "Wait"), Transition(1, 2, "Isend"),
                                 Transition(1, 2, "Wait"), Transition(0, 3, "Ireceive"), Transition(0, 3, "Wait")}));
      // node 1
      actor_set.insert(Actor(1, {Transition(0, 1, "Isend"), Transition(0, 1, "Wait"), Transition(1, 2, "Ireceive"),
                                 Transition(1, 2, "Wait")}));

      // node 2
      actor_set.insert(Actor(2, {Transition(0, 0, "Isend"), Transition(0, 0, "Wait")}));

      initState = new State(3, actor_set, {Mailbox(0), Mailbox(1), Mailbox(2)});

      UnfoldingEvent* e = new UnfoldingEvent(initState);
      UC.explore(C, {mc::EventSet()}, D, A, e, prev_exC, actor_set);

      std::cout << "\n explore full state space :\n";

      State initState1(3, actor_set, {Mailbox(0), Mailbox(1), Mailbox(2)});
      stateStack.push_back(initState1);
      // exhautiveExplore(stateStack,transList);
    } break;
  }
  clock_t end         = clock();
  double elapsed_secs = double(end - begin) / (60 * CLOCKS_PER_SEC);

  std::cout << " Time in second= " << double(end - begin) / (CLOCKS_PER_SEC) << "  \n";
  std::cout << " Time in minutes= " << elapsed_secs << "  \n";

  std::cout << " \n main() finished ";
  return 0;
}
