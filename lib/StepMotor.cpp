#include "StepMotor.h"


	StepMotor::StepMotor(GPIO_TypeDef *GPIOx_Enable, uint16_t pin_Enable,GPIO_TypeDef *GPIOx_Dir,
			uint16_t pin_Dir, TIM_HandleTypeDef *htim_PWM, uint32_t Channel)
	{

		htim_PWM-> Instance->CR1 |=  TIM_CR1_ARPE;

		//---------------------------
		// pinout
		m_GPIOx_Enable = GPIOx_Enable;
		m_GPIOx_Dir = GPIOx_Dir;
		p_htim_PWM = htim_PWM;			// pointer to taimer
		m_Channel = Channel;			// chanel taimer
		m_pin_enable = pin_Enable;		// pin enable
		m_pin_Dir = pin_Dir;

		//---------------------------
		m_speed = 0;					// now speed
		m_MaxSpeed = 0;					// max speed
		m_MinSpeed = 0;					// min speed
		//---------------------------
		m_direction = 0;				// direction 1 - left, 0 - right
		m_counterSteps = 0;				// counter steps
		m_nStepsForMotion = 0;			// all steps
		//---------------------------
		m_Retention = 0;				// retention
		//---------------------------
		typeMotion = NO_MOTION;
		//---------------------------
		m_AccelerationStep = 0;
		m_stepEndAcceleration = 0;
		m_brakeSteps = 0;
		m_stepsStartBrake = 0;

		htim_PWM-> Instance->CR1 |=  TIM_CR1_ARPE;

	}

	void StepMotor::motorService()		//вызывается в коллбэке
	{
		HAL_GPIO_WritePin(m_GPIOx_Enable, m_pin_enable, GPIO_PIN_RESET);

		if(m_direction)
		{
			HAL_GPIO_WritePin(m_GPIOx_Dir, m_pin_Dir, GPIO_PIN_SET);
		}
		else if(!m_direction)
		{
			HAL_GPIO_WritePin(m_GPIOx_Dir, m_pin_Dir, GPIO_PIN_RESET);
		}

		if(m_counterSteps < m_nStepsForMotion)
		{
			accelerationService(m_counterSteps);
			brakeService(m_counterSteps);
			m_counterSteps++;
		}
		else
		{
			m_speed = 0;
			typeMotion = NO_MOTION;
			m_counterSteps = 0;
			HAL_TIM_PWM_Stop(p_htim_PWM, m_Channel); 				// остановить шим
			setRetention(m_Retention);
		}
	}

	void StepMotor::checkMotorInCallback(TIM_HandleTypeDef *htim)
	{
		if(htim == this->p_htim_PWM)
			{
				motorService();
			}
	}

	void StepMotor::setDirection(uint8_t in_direction)
	{
		m_direction = in_direction;
	}

	uint8_t StepMotor::getDirection()
	{
		return m_direction;
	}

	void StepMotor::startMotion(uint32_t steps)
	{
		if(typeMotion == NO_MOTION)
		{
			typeMotion = ACCELERATION;
			m_nStepsForMotion = steps;
			HAL_TIM_PWM_Start_IT(p_htim_PWM, TIM_CHANNEL_1);
		}
	}

	void StepMotor::stopMotion()
	{
		HAL_TIM_PWM_Stop_IT(p_htim_PWM, TIM_CHANNEL_1);
	}

	void StepMotor::setMaxSpeed(uint32_t maxSpeed)
	{
		m_MaxSpeed = maxSpeed;
	}

	uint32_t StepMotor::getSpeed()
	{
		return m_MaxSpeed;
	}

	uint32_t StepMotor::getMaxSpeed()
	{
		return m_MaxSpeed;
	}


	void StepMotor::setMinSpeed(uint32_t speed)
	{
		m_MinSpeed = speed;
	}

	uint32_t StepMotor::getMinSpeed()
	{
		return m_MinSpeed;
	}

	void StepMotor::setRetention(bool Retention)
	{
		m_Retention = Retention;

		if(m_Retention)
			HAL_GPIO_WritePin(m_GPIOx_Enable, m_pin_enable, GPIO_PIN_RESET);
		else if(!m_Retention)
			HAL_GPIO_WritePin(m_GPIOx_Enable, m_pin_enable, GPIO_PIN_SET);
	}

	void StepMotor::setSpeed(uint32_t speed)
	{
		if(m_speed <= m_MaxSpeed)
		{
			m_speed = speed;
			int arr = HAL_RCC_GetSysClockFreq() / (speed * p_htim_PWM->Instance->ARR);
			p_htim_PWM -> Instance -> ARR = arr - 1;
			p_htim_PWM -> Instance -> CCR1 = arr / 2;
		}

	}

	void StepMotor::setAccelerationStep(uint32_t steps, uint32_t stepEndAcceleration)		// до какого шага увеличение частоты
	{
		m_AccelerationStep = m_MaxSpeed / steps;
		m_stepEndAcceleration = stepEndAcceleration;
	}

	void StepMotor::accelerationService(uint32_t i)
	{
		if (i == 0 || i > m_stepEndAcceleration)
			return;

		if(i % m_AccelerationStep == 0)	//
		{
			setSpeed(m_speed + m_AccelerationStep);
		}

	}

	void StepMotor::setBrakeMotorStep(uint32_t stepsBrake, uint32_t stepsForEndBraking)
	{
		m_brakeSteps = m_speed / stepsBrake;
		m_stepsStartBrake = m_nStepsForMotion - stepsForEndBraking;
	}

	void StepMotor::brakeService(uint32_t i)
	{
		if (i == 0 || i > m_stepsStartBrake)
			return;

		if(i % m_brakeSteps == 0)	//
		{
			setSpeed(m_speed - m_brakeSteps);
		}
	}
