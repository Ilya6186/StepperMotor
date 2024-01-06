/*
 * StepMotor.h
 *
 *  Created on: Nov 28, 2023
 *      Author: user
 */

#include "stm32f103xb.h"
#include "stm32f1xx_hal.h"
#include "main.h"

class StepMotor{

public:
	StepMotor(GPIO_TypeDef *GPIOx_Enable, uint16_t pin_Enable,GPIO_TypeDef *GPIOx_Dir,
			uint16_t pin_Dir, TIM_HandleTypeDef *htim_PWM, uint32_t Channel);


	uint32_t pwm;
	uint32_t m_counterSteps;

	private:
	GPIO_TypeDef *m_GPIOx_Enable;
	GPIO_TypeDef *m_GPIOx_Dir;
	GPIO_TypeDef *m_GPIOx_Step;
	uint16_t m_pin_enable;
	uint16_t m_pin_Dir;
	uint16_t m_pin_step;

	TIM_HandleTypeDef *p_htim_PWM;

	uint32_t m_Channel;
	uint8_t m_direction;
	uint32_t m_nStepsforRun;
	uint32_t m_MaxSpeed;
	uint32_t m_MinSpeed;
	bool m_Retention;
	uint32_t m_AccelerationKoefficient;
	uint32_t m_LastAcceleration_time;
	uint32_t m_AccelerationStep;
	bool m_inMotion;
	uint32_t m_speed;
	uint32_t m_stepEndAccep;

	bool m_FlagRazgona;
	bool m_FlagTormoza;

	public:
	void setDirection(uint8_t direction);
	void checkMotorInCallback(TIM_HandleTypeDef *htim);
	inline uint8_t getDirection();
	void startMotion(uint32_t steps);
	void stopMotion();
	void accelerationService(int i);
	void setMaxSpeed(uint32_t speed);
	uint32_t getSpeed();
	void setAccelerationStep(uint32_t step,  uint32_t stepEndAccep);
	void setSpeed(uint32_t speed);
	uint32_t getMaxSpeed();
	void setMinSpeed(uint32_t speed);
	uint32_t getMinSpeed();
	void setRetention(bool);



	private:
	void motorService();
};




