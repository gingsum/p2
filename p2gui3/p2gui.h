/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class p2gui */

#ifndef _Included_p2gui
#define _Included_p2gui
#ifdef __cplusplus
extern "C" {
#endif
#undef p2gui_FOCUS_TRAVERSABLE_UNKNOWN
#define p2gui_FOCUS_TRAVERSABLE_UNKNOWN 0L
#undef p2gui_FOCUS_TRAVERSABLE_DEFAULT
#define p2gui_FOCUS_TRAVERSABLE_DEFAULT 1L
#undef p2gui_FOCUS_TRAVERSABLE_SET
#define p2gui_FOCUS_TRAVERSABLE_SET 2L
#undef p2gui_TOP_ALIGNMENT
#define p2gui_TOP_ALIGNMENT 0.0f
#undef p2gui_CENTER_ALIGNMENT
#define p2gui_CENTER_ALIGNMENT 0.5f
#undef p2gui_BOTTOM_ALIGNMENT
#define p2gui_BOTTOM_ALIGNMENT 1.0f
#undef p2gui_LEFT_ALIGNMENT
#define p2gui_LEFT_ALIGNMENT 0.0f
#undef p2gui_RIGHT_ALIGNMENT
#define p2gui_RIGHT_ALIGNMENT 1.0f
#undef p2gui_serialVersionUID
#define p2gui_serialVersionUID -7644114512714619750i64
#undef p2gui_serialVersionUID
#define p2gui_serialVersionUID 4613797578919906343i64
#undef p2gui_INCLUDE_SELF
#define p2gui_INCLUDE_SELF 1L
#undef p2gui_SEARCH_HEAVYWEIGHTS
#define p2gui_SEARCH_HEAVYWEIGHTS 1L
#undef p2gui_OPENED
#define p2gui_OPENED 1L
#undef p2gui_serialVersionUID
#define p2gui_serialVersionUID 4497834738069338734i64
#undef p2gui_DEFAULT_CURSOR
#define p2gui_DEFAULT_CURSOR 0L
#undef p2gui_CROSSHAIR_CURSOR
#define p2gui_CROSSHAIR_CURSOR 1L
#undef p2gui_TEXT_CURSOR
#define p2gui_TEXT_CURSOR 2L
#undef p2gui_WAIT_CURSOR
#define p2gui_WAIT_CURSOR 3L
#undef p2gui_SW_RESIZE_CURSOR
#define p2gui_SW_RESIZE_CURSOR 4L
#undef p2gui_SE_RESIZE_CURSOR
#define p2gui_SE_RESIZE_CURSOR 5L
#undef p2gui_NW_RESIZE_CURSOR
#define p2gui_NW_RESIZE_CURSOR 6L
#undef p2gui_NE_RESIZE_CURSOR
#define p2gui_NE_RESIZE_CURSOR 7L
#undef p2gui_N_RESIZE_CURSOR
#define p2gui_N_RESIZE_CURSOR 8L
#undef p2gui_S_RESIZE_CURSOR
#define p2gui_S_RESIZE_CURSOR 9L
#undef p2gui_W_RESIZE_CURSOR
#define p2gui_W_RESIZE_CURSOR 10L
#undef p2gui_E_RESIZE_CURSOR
#define p2gui_E_RESIZE_CURSOR 11L
#undef p2gui_HAND_CURSOR
#define p2gui_HAND_CURSOR 12L
#undef p2gui_MOVE_CURSOR
#define p2gui_MOVE_CURSOR 13L
#undef p2gui_NORMAL
#define p2gui_NORMAL 0L
#undef p2gui_ICONIFIED
#define p2gui_ICONIFIED 1L
#undef p2gui_MAXIMIZED_HORIZ
#define p2gui_MAXIMIZED_HORIZ 2L
#undef p2gui_MAXIMIZED_VERT
#define p2gui_MAXIMIZED_VERT 4L
#undef p2gui_MAXIMIZED_BOTH
#define p2gui_MAXIMIZED_BOTH 6L
#undef p2gui_serialVersionUID
#define p2gui_serialVersionUID 2673458971256075116i64
#undef p2gui_EXIT_ON_CLOSE
#define p2gui_EXIT_ON_CLOSE 3L
/*
 * Class:     p2gui
 * Method:    date
 * Signature: (I)[I
 */
JNIEXPORT jintArray JNICALL Java_p2gui_date
  (JNIEnv *, jobject, jint);

/*
 * Class:     p2gui
 * Method:    size
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_p2gui_size
  (JNIEnv *, jobject, jint);

/*
 * Class:     p2gui
 * Method:    name
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_p2gui_name
  (JNIEnv *, jobject, jint);

/*
 * Class:     p2gui
 * Method:    type
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_p2gui_type
  (JNIEnv *, jobject, jint);

/*
 * Class:     p2gui
 * Method:    resetData
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_p2gui_resetData
  (JNIEnv *, jobject);

/*
 * Class:     p2gui
 * Method:    setCurrDir
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_p2gui_setCurrDir
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif
