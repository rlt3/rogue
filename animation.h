#ifndef ANIMATION_H
#define ANIMATION_H

/*
 * This struct holds information on special
 * animations that need to be displayed.
 * These includes things like attacking,
 * death animations, etc.
 *
 * The way it works is the game keeps track
 * of the CURTIME(). The struct holds the
 * time frame on when to update the frames.
 *
 * So, every .25 seconds, update the frame.
 *
 * Otherwise, that particular Animation
 * frame will continue to be drawn so it
 * actually appears to the player.
 *
 * These Animations are held in an array
 * of size of the current floor. When the
 * animation is at the end of its frame,
 * it gets removed, or NULLed out.
 */

typedef struct Animation {
  Entity *entity;
  uint8_t state;
  uint8_t frame;
  float time;
} Animation;

#endif
