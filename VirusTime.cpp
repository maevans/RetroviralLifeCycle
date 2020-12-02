//
//  VirusTime.cpp
//  RetroviralLifeCycle
//
//  Created by Mahalia Evans
//

#include "VirusTime.hpp"

// -----------------------------
//update(int milliseconds)   // 16.6ms = 1/60th a second.
//  pos+=vel*milliseconds;
//
//
//initializeState()
//{
//  state = 0;
//  Time2Event = 1;
//}
//ProcessState(int milliseconds)
//{
//  switch(EventStrategy)
//  {
//      case:  WAIT_FOR_TIMER
//
//    Time2Event-=milliseconds;
//    if (Time2Event < 0)
//    {
//      switch(state)
//      {
//        case 0:                // Wait before we start to move.
//                  vel = 1;
//                  Time2Event += 3;
//                  state = 1;
//                  break;
//
//        case 1:
//                  vel = 0;
//                  eventStrategy=WAIT_FOR_MESSAGE;
//                  state = 2'
//                  break;
//
//        case 2:
//                    if(distance(obj1,obj2) < 1)
//                  state =3;
//                    Time2Event+=milliseconds;
//                  break;
//        case 3:
//                  drawExplosion();
//
//
//        }
//    }
//      break;   // Wait for Timer.
//     case:  WAIT_FOR_MESSAGE
//       getMessage()
//       ProcessMessage();
//      break;
//  }
//  {
//}
//
