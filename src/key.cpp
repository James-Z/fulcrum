if( XPending( dpy ) )
{
	//
	XNextEvent (dpy, &xev);
	//
	switch(xev.type) {
		case Expose:
			scene_out_test->update_scene();
			scene_out_test->render_scene();
			glXSwapBuffers (dpy, win);
			break;
		case KeyPress:
				XKeyEvent *xke;
				int ks;
				int key;

				ke=&xev.xkey;
				kGUI::SetKeyShift((ke->state&ShiftMask)!=0);
				kGUI::SetKeyControl((ke->state&ControlMask)!=0);
				ks=XLookupKeysym(ke,(ke->state&ShiftMask)?1:0);

				//todo handle f1-f12
				key=0;
				switch(ks) {
					case XK_Escape:
						glXMakeCurrent (dpy, None, NULL);
						glXDestroyContext (dpy, glc);
						XDestroyWindow (dpy, win);
						XCloseDisplay (dpy);
						exit (0);
					case XK_a:
						scene_out_test->_controller_in_scene->move_object( CLOCK_WISE_ROTATION );
						break;
					case XK_d:
						scene_out_test->_controller_in_scene->move_object( MOTION_STATE::ANTI_CLOCK_WISE_ROTATION );
						break;
					case XK_w:
						scene_out_test->_controller_in_scene->move_object( MOTION_STATE::FORWORD );
						break;
					case XK_s:
						scene_out_test->_controller_in_scene->move_object( BACKWARD );
						break;
					default:
						break;

				}
		case KeyRelease:
				XKeyEvent *ke;
				int key;

				ke=&m_e.xkey;
				key=ConvertKey(XLookupKeysym(ke,0));
				if(key)
					kGUI::SetKeyState(key,false);
				break;
				switch(ks) {
					case XK_Escape:
						glXMakeCurrent (dpy, None, NULL);
						glXDestroyContext (dpy, glc);
						XDestroyWindow (dpy, win);
						XCloseDisplay (dpy);
						exit (0);
					case XK_a:
						scene_out_test->_controller_in_scene->move_object( MOTION_STATE::STOP );
						break;
					case XK_d:
						scene_out_test->_controller_in_scene->move_object( MOTION_STATE::STOP  );
						break;
					case XK_w:
						scene_out_test->_controller_in_scene->move_object( MOTION_STATE::STOP );
						break;
					case XK_s:
						scene_out_test->_controller_in_scene->move_object( MOTION_STATE::STOP );
						break;
					default:
						break;

				scene_out_test->update_scene();
				scene_out_test->render_scene();
				glXSwapBuffers(dpy, win);
	}
}
