//
//  VirusTime.cpp
//  RetroviralLifeCycle
//
//  Created by Mahalia Evans
//

/*
 ********** Simulation Function **********
 _________________________________________
 * Generate Host Cell
 ** Set Retrovirus outside of Host Cell Membrane
 ** For every Retrovirus, give it direction
 ** While(not end of simulation)
 **** time = increment_simulation_time();
 **** for every Retrovirus
 ****** move the Retrovirus along its direction based on time
 ** End of Simulation
 ****** generate many retroviruses outside of Host Cell Membrane
*/

// -----------------------------
// Update Simulation
//void updateSimulation(std::vector<Entity>& entities, double previous_update_time, double current_time) {
//
//  double delta_time = current_time - previous_update_time;   // Change in Time
//
//  for(int i = 0; i < entities.size(); ++i) {   // Size of Objs
//
//      // To Updates Position -> Position, Direction, Speed & Time
//    entities[i].position = entities[i].position + entities[i].direction * speed * delta_time;
//
//  }
//}


int msecs = 20;
int curr_frame = 0;
float deltaTime;

void updateTime(int s){
    
    // Update the current frame based on frame rate & delta time
    curr_frame += msecs * deltaTime;
}
//void createPhase(){
//
//    int phase = 0;
//}
//
//void processTime(int ms){
//
//    if(curr_frame < 0){
//        switch (phase) {
//            case 0:
//                Binding();
//                phase = 1;
//                break;
//            case 1:
//                Fusion();
//                phase = 2;
//                break;
//            case 2:
//                Uncoating();
//                phase = 3;
//                break;
//            case 3:
//                ReverseTranscription();
//                phase = 4;
//                break;
//            case 4:
//                Entry();
//                phase = 5;
//                break;
//            case 5:
//                Transcription();
//                phase = 6;
//                break;
//            case 6:
//                Assembly();
//                phase = 7;
//            case 7:
//                Budding();
//                break;
//            default:
//                InitialScene();
//                break;
//        }
//    }
//}
