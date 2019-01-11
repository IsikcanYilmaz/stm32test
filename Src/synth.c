
#include "tim.h"
#include "synth.h"
#include "dac.h"


uint16_t counters[NUM_OSCILLATORS], output;
const uint32_t pitchtbl[] = {16384,
   15464,14596,13777,13004,12274,11585,10935,10321,9742,9195,8679,
   8192,7732,7298,6889,6502,6137,5793,5468,5161,4871,4598,4340,
   4096,3866,3649,3444,3251,3069,2896,2734,2580,2435,2299,2170,
   2048,1933,1825,1722,1625,1534,1448,1367,1290,1218,1149,1085,
   1024,967,912,861,813,767,724,683,645,609,575,542,
   512,483,456,431,406,384,362,342,323,304,287,271,
   256,242,228,215,203,192,181,171,161,152,144,136,
   128,121,114,108 ,102,96,91,85,81,76,72,68,64};

void synth_init(){
  HAL_TIM_Base_Stop(&htim2);
  HAL_TIM_Base_Stop(&htim6);
  HAL_TIM_Base_Stop(&htim21);
  HAL_TIM_Base_Stop(&htim22);
}

void play_note(uint8_t note, uint8_t velocity){
  TIM22_Config(pitchtbl[note]);
}

void synth_output(){
  uint16_t output;
  output = counters[3];
  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, output);
}

void make_sound(){
  counters[0] = __HAL_TIM_GetCounter(&htim2);
  counters[1] = __HAL_TIM_GetCounter(&htim6);
  counters[2] = __HAL_TIM_GetCounter(&htim21);
  counters[3] = __HAL_TIM_GetCounter(&htim22);

}

void update_lfos(){

}

void note_on(uint8_t key, uint8_t vel){
  uint32_t note = pitchtbl[key];
  test_tone();
}

void note_off(uint8_t key){
  synth_init();
  
}

void test_tone(){
  play_note(pitchtbl[35], NULL);

}

void mixer(){
  make_sound();
  synth_output();
  //update_lfos();
}
