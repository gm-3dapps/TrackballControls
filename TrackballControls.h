/**
* Initial @author Eberhard Graether / http://egraether.com/
* C++ port by Michael Ivanov (sasmaster) 
*/

#pragma once
#ifndef TRACKBALL_CONTROLLS_H
#define TRACKBALL_CONTROLLS_H

 
#include "GL/glew.h"

#include "glm.hpp"
#include <stdint.h>


struct GLFWwindow;
namespace sasmaster{

	class  Camera3D{

	public:

		glm::vec3 m_eye, m_up;
		glm::mat4 m_viewMatr;

		Camera3D(const glm::vec3& pos);

		void LookAt(const glm::vec3& target);
		 


	};
	/**
	* The class is a singleton.
	*/
	class TrackballControls
	{
	 
	public:
		/**
		* @param cam = pointer to active camera object.
		* @param screenSize - size of the window screen.
		*/
		static TrackballControls& GetInstance(Camera3D* cam,glm::vec4 screenSize);

		void Init(GLFWwindow *win);

		void Update();


		float m_rotateSpeed;
		float m_zoomSpeed;
		float m_panSpeed;
		float m_dynamicDampingFactor;
		float m_minDistance;
		float m_maxDistance;
		bool m_enabled;
		bool m_noRotate;
		bool m_noZoom;
		bool m_noPan;
		bool m_noRoll;
		bool m_staticMoving;

	private:
		TrackballControls(Camera3D* cam,glm::vec4 screenSize);


		void MouseUp();

		void KeyUp();

		void MouseDown(int button, int action, int mods,int xpos,int ypos);

		void MouseMove(int xpos, int ypos);

		void KeyDown(int key);

		void MouseWheel(double xoffset ,double yoffset);

		glm::vec3 GetMouseProjectionOnBall(int clientX, int clientY);

		glm::vec2 GetMouseOnScreen(int clientX, int clientY);

		void  RotateCamera();

		void ZoomCamera();

		void PanCamera();

		void CheckDistances();

		enum class TCB_STATE:uint8_t{
			NONE,
			ROTATE,
			ZOOM,
			PAN
		};

		Camera3D* m_pCam;
		glm::vec4 m_screen;


		glm::vec3 m_target;
		glm::vec3 m_lastPos;
		glm::vec3 m_eye;
		glm::vec3 m_rotStart;
		glm::vec3 m_rotEnd;
		glm::vec2 m_zoomStart;
		glm::vec2 m_zoomEnd;
		glm::vec2 m_panStart;
		glm::vec2 m_panEnd;
		TCB_STATE m_state;
		TCB_STATE m_prevState;

		static uint32_t m_keys[3];

		static void MouseMoveCallBack(GLFWwindow* win, double xpos, double ypos) ;
		static void MouseButtonCallBack(GLFWwindow* win ,int button,int action,int mods);
		static void MouseScrollCallBack(GLFWwindow* win, double xpos, double ypos);
		static void KeyboardCallBack(GLFWwindow* win,int key,int scancode,int action,int mods);





	};

	inline glm::vec2 TrackballControls::GetMouseOnScreen(int clientX, int clientY)
	{
		return glm::vec2(
			(float)(clientX - m_screen.x) / m_screen.z,
			(float)(clientY - m_screen.y) / m_screen.w
			);
	}


	inline void TrackballControls::MouseUp(){

		if(!m_enabled)return;

		m_state = TCB_STATE::NONE;

	}

	inline void TrackballControls::KeyUp(){

		if (!m_enabled) { return; }

		m_state = m_prevState;

	}

}

#endif//TRACKBALL_CONTROLLS_H

