#pragma once
#include "stdafx.h"

/**
 * Convert a local point to a world point for an actor.
 * @param  a The actor
 * @param  x Local X coordinate
 * @param  y Local Y coordinate
 * @return World Coordinate
 */
Vector2 localToWorld(Actor *a, float x, float y);

/**
 * Convert a local point to a world point for an actor.
 * @param  a The actor
 * @param  v The local point
 * @return World Coordinate
 */
Vector2 localToWorld(Actor *a, Vector2 &v);/**
 * Draw a line with openGL.
 * @param ax start x in world coordinates
 * @param ay start y  in world coordinates
 * @param bx end x in world coordinates
 * @param by end y in world coordinates
 * @param color line color
 * @param width line width in pixels
 */
void drawLine(float ax, float ay, float bx, float by, Color color, float width);

/**
 * @param a     start point in world coordinates
 * @param b     end point in world coordinates
 * @param color line color
 * @param width line width in pixels
 */
void drawLine(Vector2 a, Vector2 b, Color color, float width);