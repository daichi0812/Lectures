/*
 * File:         e-puck�p�R���g���[����E3-1�p�����\�[�X�t�@�C��
 * Date:         2019/5/7
 * Description:  �p�x�Z���T����т���Ɋւ�鏔�֐��̎���
 */
/*
 * ���{�b�g�m�[�h�p�̃��C�u�����A����ъe��Z���T�m�[�h�p���C�u�����̓ǂݍ���
 * robot.h				: ���{�b�g�m�[�h
 * position_sensor.h	: �p�x�Z���T�m�[�h
 */
#include <math.h>
#include <webots/robot.h>
#include <webots/position_sensor.h>
#include "my_position_sensor_utility.h"

#define TIME_STEP	32		// ���{�b�g�̐������[ms]
#define LEFT	 	0		// ���E�����ʂ��邽�߂̒萔�i����0�Ƃ���j
#define RIGHT	 	1		// ���E�����ʂ��邽�߂̒萔�i�E��1�Ƃ���j

#define WL_R_SIMU	0.02	// ���{�b�g�̎ԗ֔��a(WEBOTS��)[m]
#define AX_L_SIMU	0.052	// ���{�b�g�̎Ԏ���(WEBOTS��)[m]

#define WL_R_REAL	0.02	// ���{�b�g�̎ԗ֔��a(���@��)[m]
#define AX_L_REAL	0.052	// ���{�b�g�̎Ԏ���(���@��)[m]

#define MAX_POS_VALUE	205.78304	// �p�x�Z���T����擾����l�̍ő�[rad](=0.00628*pow(2,15))

/* �p�x�Z���T�������� */
POS_SENSOR initialize_position_sensors(void)
{
  POS_SENSOR ret;	// �߂�l�Ƃ��Ă̊p�x�Z���T�p�\����

  ret.mode = wb_robot_get_mode();
  ret.tag[LEFT]  = wb_robot_get_device("left wheel sensor");	// �^�O�̎擾
  ret.tag[RIGHT] = wb_robot_get_device("right wheel sensor");	// �^�O�̎擾
  wb_position_sensor_enable(ret.tag[LEFT],  TIME_STEP);	// TIME_STEP�����œ���J�n
  wb_position_sensor_enable(ret.tag[RIGHT], TIME_STEP);	// TIME_STEP�����œ���J�n
  ret = reset_position_sensors(ret);	// ����l�����Z�b�g

  return ret;
}

/* �p�x�Z���T�̑���l���擾 */
POS_SENSOR get_position_sensors(POS_SENSOR pos_sensor)
{
  POS_SENSOR ret = pos_sensor;	// �߂�l�Ƃ��Ă̊p�x�Z���T�p�\����
  double value[2];	// �p�x�Z���T�̑���l�i�����H�j

  ret.mode = wb_robot_get_mode();	// ���{�b�g�̓��샂�[�h�̎擾
  if(ret.mode != pos_sensor.mode			// ���샂�[�h���؂�ւ������A
		|| isnan(ret.pre_pos[LEFT]) ){	// �܂��́Aposition0[]��NaN��������A
    ret = reset_position_sensors(ret);		// ����l�����Z�b�g
  }

  // �p�x�Z���T�̐��f�[�^���擾
  value[LEFT]  = wb_position_sensor_get_value(ret.tag[LEFT]);
  value[RIGHT] = wb_position_sensor_get_value(ret.tag[RIGHT]);

  // �I�[�o�[�t���[�̏����i����l��-205.78304����+205.78304�ɂȂ�Ƃ��j
  if(value[LEFT] - ret.pre_pos[LEFT] >  MAX_POS_VALUE)
	ret.pre_pos[LEFT]  += 2.0 * MAX_POS_VALUE;
  else if(value[LEFT] - ret.pre_pos[LEFT] < -MAX_POS_VALUE)
	ret.pre_pos[LEFT]  -= 2.0 * MAX_POS_VALUE;
  if(value[RIGHT] - ret.pre_pos[RIGHT] >  MAX_POS_VALUE)
	ret.pre_pos[RIGHT] += 2.0 * MAX_POS_VALUE;
  else if(value[RIGHT] - ret.pre_pos[RIGHT] < -MAX_POS_VALUE)
	ret.pre_pos[RIGHT] -= 2.0 * MAX_POS_VALUE;

  // �p�x�Z���T�̊�̊p�x����̉�]�p�x���v�Z
  ret.position[LEFT]  += value[LEFT]  - ret.pre_pos[LEFT];
  ret.position[RIGHT] += value[RIGHT] - ret.pre_pos[RIGHT];
  ret.pre_pos[LEFT]  = value[LEFT];
  ret.pre_pos[RIGHT] = value[RIGHT];

  return ret;
}

/* �p�x�Z���T�̑���l�����Z�b�g */
POS_SENSOR reset_position_sensors(POS_SENSOR pos_sensor)
{
  POS_SENSOR ret = pos_sensor;	// �߂�l�Ƃ��Ă̊p�x�Z���T�p�\����

  // ���݂̊p�x����̊p�x�ɐݒ�
  ret.pre_pos[LEFT]  = wb_position_sensor_get_value(ret.tag[LEFT]);
  ret.pre_pos[RIGHT] = wb_position_sensor_get_value(ret.tag[RIGHT]);
  ret.position[LEFT]  = 0.0;
  ret.position[RIGHT] = 0.0;

  return ret;
}

/* �p�x�Z���T�̑���l�����Ƀ��{�b�g�̈ړ��������v�Z */
double compute_length(POS_SENSOR pos_sensor)
{
  double length;
  double avr_position; // �p�x�Z���T�̑���l�̕���

  avr_position = (pos_sensor.position[LEFT] + pos_sensor.position[RIGHT]) / 2.0;
  // �ړ������̌v�Z�B���샂�[�h��WEBOTS�����@���Ńp�����[�^��ύX
  if(pos_sensor.mode == WB_MODE_SIMULATION){
    length = avr_position * WL_R_SIMU;
  }
  else{
    length = avr_position * WL_R_REAL;
  }

  return length;
}

/* �p�x�Z���T�̑���l�����Ƀ��{�b�g�̐���p�x���v�Z */
double compute_orientation(POS_SENSOR pos_sensor)
{
  double orientation;
  double half_diff_pos; // �p�x�Z���T�̑���l�̍��̔���

  half_diff_pos = (pos_sensor.position[RIGHT] - pos_sensor.position[LEFT]) / 2.0;
  // ����p�x�̌v�Z�B���샂�[�h��WEBOTS�����@���Ńp�����[�^��ύX
  if(pos_sensor.mode == WB_MODE_SIMULATION){
    orientation = (half_diff_pos*WL_R_SIMU)/(AX_L_SIMU/2.0);
  }
  else{
    orientation = (half_diff_pos*WL_R_REAL)/(AX_L_REAL/2.0);
  }

  return orientation;
}
