// AnimationProgramming.cpp : Defines the entry point for the console application.
//
#include "Engine.h"
#include "Simulation.h"
#include "Skeleton.h"
#include "AnimationClip.h"
#include "Rendering.h"
#include "Animator.h"

// true --> display 
constexpr bool display_skeleton = true;

// true --> start blending between walk and run
constexpr bool blending = true;

// If blending = false
// true --> play walk animation
// false --> play run animation
constexpr bool play_walk_only = false;

// Time between two blending : play only one full animation
constexpr float time_between_blending = 3.0f;

//constexpr float blending_time = 0.5f;

class CSimulation : public ISimulation
{
	
private:
	Skeleton m_skeleton;
	Animator m_animator;
	float m_blendingRatio = 0.0f;
	float m_timeToUpBlending = 0.2f;
	float m_timeBuffer = time_between_blending;
	
	bool m_isBlending = false;
	bool m_toWalking = true;
		
	virtual void Init() override
	{
		m_skeleton.Init();

		m_animator.AddAnimationClip(&m_skeleton, "ThirdPersonRun.anim", 1.0f);
		m_animator.AddAnimationClip(&m_skeleton, "ThirdPersonWalk.anim", 1.0f);
		
	}

	virtual void Update(float frameTime) override
	{
		Rendering::DrawAxis();
		UpdateBlendingRatio(frameTime);

		m_animator.MutateAnimationClipByIndex(0).UpdateKeyToDraw(frameTime);

		m_animator.MutateAnimationClipByIndex(1).UpdateKeyToDraw(frameTime);
		

		if (blending)
		{
			if (m_toWalking)
			{
				m_animator.BlendAnimation(m_blendingRatio, m_skeleton, m_animator.MutateAnimationClipByIndex(1), m_animator.MutateAnimationClipByIndex(0));
			}
			else
			{
				m_animator.BlendAnimation(m_blendingRatio, m_skeleton, m_animator.MutateAnimationClipByIndex(0), m_animator.MutateAnimationClipByIndex(1));
			}
			
		}
		else
		{
			if (play_walk_only)
			{

				m_animator.MutateAnimationClipByIndex(0).UpdateAnimMatrices(frameTime);
				m_animator.MutateAnimationClipByIndex(0).SendAnimMatricesToShader();
				//_animator.MutateAnimationClipByIndex(0).DrawAnimSkeleton(keyToDraw);
			}
			else
			{
				m_animator.MutateAnimationClipByIndex(1).UpdateAnimMatrices(frameTime);
				m_animator.MutateAnimationClipByIndex(1).SendAnimMatricesToShader();
				//m_animator.MutateAnimationClipByIndex(1).DrawAnimSkeleton(keyToDraw);
			}
		}
		
		//m_skeleton.DrawBindPose();
		
	}

	void UpdateBlendingRatio(float deltaTime)
	{

		m_timeBuffer -= deltaTime;
		
		if(!m_isBlending)
		{
			if (m_timeBuffer < 0.0f)
			{
				m_isBlending = true;
				m_timeBuffer = m_timeToUpBlending;
			}
		}

		
		if (m_timeBuffer <= 0.0f)
		{
			m_blendingRatio += 0.1f;
			m_timeBuffer += m_timeToUpBlending;
		}

		if (m_blendingRatio > 1.0f)
		{
			m_timeBuffer = time_between_blending;
			m_isBlending = false;
			m_blendingRatio = 0.0f;
			m_toWalking = !m_toWalking;
		}
	}
};



int main()
{
	CSimulation simulation;

	Run(&simulation, 1400, 800);
	
	return 0;
}