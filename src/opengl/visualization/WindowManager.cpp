/*!
 * Copyright (C) tkornuta, IBM Corporation 2015-2019
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*!
 * \file WindowManager.cpp
 * \brief Definitions of methods of WindowManager class.
 * \author: tkornuta
 * \date Nov 19, 2015
 */

#include <opengl/visualization/WindowManager.hpp>
#include <opengl/visualization/Window.hpp>

#include <logger/Log.hpp>

#include <exception>

namespace mic {
  namespace opengl {
    namespace visualization {


      // Init application instance - as NULL.
      boost::atomic<WindowManager*> WindowManager::instance_(NULL);


      // Initilize singleton instantiation mutex.
      boost::mutex WindowManager::instantiation_mutex;

      WindowManager* WindowManager::getInstance() {
        // Try to load the instance - first check.
        WindowManager* tmp = instance_.load(boost::memory_order_consume);
        // If instance does not exist.
        if (!tmp) {
          // Enter critical section.
          boost::mutex::scoped_lock guard(instantiation_mutex);
          // Try to load the instance - second check.
          tmp = instance_.load(boost::memory_order_consume);
          // If still does not exist - create new instance.
          if (!tmp) {
            tmp = new WindowManager;
            instance_.store(tmp, boost::memory_order_release);
          }//: if
          // Exit critical section.
        }//: if
        // Return instance.
        return tmp;
      }

      void WindowManager::registerWindow(mic::opengl::visualization::Window* window_) {
        LOG(LTRACE) << "WindowManager::registerWindow";
        if (window_ != NULL) {
          LOG(LDEBUG) << "Registering window " << window_->getId();
          window_registry.insert(id_win_pair_t(window_->getId(), window_));
        }//: if
      }

      mic::opengl::visualization::Window* WindowManager::findWindow(unsigned int id_) {
        LOG(LTRACE) << "WindowManager::findWindow";
        // Find window with given id.
        id_win_it_t it = window_registry.find(id_);
        if (it != window_registry.end())
          return it->second;
        else {
          LOG(LWARNING) << "Window " << id_ << " not found";
          return NULL;
        }//: else
      }

      void WindowManager::displayHandler(void) {
        LOG(LTRACE) << "Display handler of " << glutGetWindow() << " window";

        // If opengl "finished" - throw exception to break the GLUT loop!
        if (APP_STATE->Quit()) {
          //LOG(LERROR) << "ESC pressed - throwing an exception!";
          throw std::exception();
        }

        //printf("Display handler of %d window!\n", glutGetWindow());
        Window* w = VGL_MANAGER->findWindow(glutGetWindow());
        if (w != NULL) {
          w->displayHandler();
        }//: if
      }

      void WindowManager::mouseHandler(int button, int state, int x, int y) {
        LOG(LTRACE) << "Mouse handler of " << glutGetWindow() << " window";
        Window* w = VGL_MANAGER->findWindow(glutGetWindow());
        if (w != NULL) {
          w->mouseHandler(button, state, x, y);
        }//: if
      }

      void WindowManager::reshapeHandler(int width_, int height_) {
        LOG(LTRACE) << "Reshape handler of " << glutGetWindow() << " window";
        Window* w = VGL_MANAGER->findWindow(glutGetWindow());
        if (w != NULL) {
          w->reshapeHandler(width_, height_);
        }//: if
      }

      void WindowManager::keyboardHandler(unsigned char key, int x, int y) {
        LOG(LTRACE) << "Keyboard handler of " << glutGetWindow() << " window";
        Window* w = VGL_MANAGER->findWindow(glutGetWindow());
        if (w != NULL) {
          w->keyboardHandler(key);
        }//: if
      }

      void WindowManager::idle(void) {
        LOG(LTRACE) << "WindowManager::idle";
        WindowManager* wm = VGL_MANAGER;

        for (id_win_it_t it = wm->window_registry.begin(); it != wm->window_registry.end(); it++) {
          // Activate window.
          glutSetWindow(it->first);
          // Update its content.
          glutPostRedisplay();
        }//: end

      }

      void WindowManager::terminateWindows(void) {
        LOG(LTRACE) << "WindowManager::terminateWindows";
        /*WindowManager* wm = VGL_MANAGER;

         for (id_win_it_t it = wm->window_registry.begin(); it != wm->window_registry.end(); it++) {
          LOG(LSTATUS) << "Window " << it->first << " being destroyed...";
          // Activate window.
          glutSetWindow(it->first);
          // Destroy window.
          glutDestroyWindow(it->first);
        }//: end

        LOG(LERROR) << "WindowManager::terminateWindows - done destroying windows";*/
        
        //boost::mutex::scoped_lock unlock(APP_STATE->dataSynchronizationMutex());
      }

      WindowManager::WindowManager() {
        //exit_signal = false;
      }

      WindowManager::~WindowManager() {
        // TODO Auto-generated destructor stub
      }

      void WindowManager::initializeGLUT(int argc, char *argv[]) {
        LOG(LTRACE) << "WindowManager::initializeGLUT";
        // Initialize GLUT.
        glutInit(&argc, argv);

        // Attach the idle handler function.
        glutIdleFunc(VGL_MANAGER->idle);

      }

      void WindowManager::startVisualizationLoop() {
        LOG(LTRACE) << "WindowManager::startVisualizationLoop";
        // Change application state.
        APP_STATE->startUsingOpenGL();
        try
        {
        	// Run main OpenGL loop (sadly, it must be executed in the same i.e. MAIN program thread).
            LOG(LTRACE) << "glutMainLoop()";
        	glutMainLoop();
        }
       	catch(...)
        {
       		LOG(LTRACE) << "Exiting glutMainLoop";
        }
        // Change application state.
        APP_STATE->stopUsingOpenGL();
      }

    } /* namespace visualization */
  } /* namespace opengl */
} /* namespace mic */
