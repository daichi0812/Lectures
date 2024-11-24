/*
 * File:         e-puck�p�R���g���[����E3-1�p�w�b�_�t�@�C��
 * Date:         2019/5/7
 * Description:  �p�x�Z���T����т���Ɋւ�鏔�֐��̐錾
 */

/* ���E�̎ԗւ̊p�x�Z���T�p�\���̂̐錾 */
typedef struct{
  WbDeviceTag tag[2];	// �f�o�C�X�^�O
  double position[2];	// �p�x�Z���T�̑���l[rad]
  double pre_pos[2];	// �O��擾�����p�x�Z���T�̒l[rad]
  WbRobotMode mode;		// ���{�b�g�̓��샂�[�h
} POS_SENSOR;

/* �p�x�Z���T�������� */
POS_SENSOR initialize_position_sensors(void);

/* �p�x�Z���T�̑���l���擾 */
POS_SENSOR get_position_sensors(POS_SENSOR pos_sensor);

/* �p�x�Z���T�̑���l�����Z�b�g */
POS_SENSOR reset_position_sensors(POS_SENSOR pos_sensor);

/* �p�x�Z���T�̑���l�����Ƀ��{�b�g�̈ړ��������v�Z */
double compute_length(POS_SENSOR pos_sensor);

/* �p�x�Z���T�̑���l�����Ƀ��{�b�g�̐���p�x���v�Z */
double compute_orientation(POS_SENSOR pos_sensor);

