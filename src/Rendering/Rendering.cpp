#include "Rendering.h"

#include <utility>

void drawLine(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void drawTriangle(SDL_Renderer *renderer, const Face &triangle, const Colour c) {
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    drawLine(renderer, triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y);
    drawLine(renderer, triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y);
    drawLine(renderer, triangle.points[2].x, triangle.points[2].y, triangle.points[0].x, triangle.points[0].y);
}

void drawFilledTriangle(SDL_Renderer *renderer, const Face &triangle, const Colour c) {
    Vec3 top = triangle.points[0];
    Vec3 mid = triangle.points[1];
    Vec3 bot = triangle.points[2];

    // Ignore degen triangles
    if (top.y == mid.y && mid.y == bot.y)
    {
        return;
    }
    if (top.x == mid.x && mid.x == bot.x)
    {
        return;
    }

    // Sort the three points of the triangle according to their y component
    if(top.y < mid.y)
    {
        std::swap(top, mid);
    }
    if(top.y < bot.y)
    {
        std::swap(top, bot);
    }
    if(mid.y < bot.y)
    {
        std::swap(mid, bot);
    }

    // Draw bounding line to make sure top and bottom end points are drawn
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    drawLine(renderer, bot.x, bot.y, mid.x, mid.y);
    drawLine(renderer, mid.x, mid.y, top.x, top.y);

    float heightBotTop = top.y - bot.y + 1;
    // Draw bottom half of triangle
    float heightBotMid = mid.y - bot.y;
    if (heightBotMid > 0)
    {
        for (int y = bot.y; y <= mid.y; y++)
        {
            float coverageBotTop = (y - (int) bot.y)/heightBotTop;
            float coverageBotMid = (y - (int) bot.y)/heightBotMid;

            if (coverageBotMid > 1)
            {
                break;
            }

            Vec3 pointBotTop = bot + (top - bot) * coverageBotTop;
            Vec3 pointBotMid = bot + (mid - bot) * coverageBotMid;

            drawLine(renderer, (int) pointBotMid.x, y, (int) pointBotTop.x, y);
        }
    }

    // Draw bottom half of triangle
    float heightMidTop = top.y - mid.y;
    if (heightMidTop > 0)
    {
        for (int y = mid.y; y <= top.y; y++)
        {
            float coverageBotTop = (y - (int) bot.y)/heightBotTop;
            float coverageMidTop = (y - (int) mid.y)/heightMidTop;

            if (coverageMidTop > 1)
            {
                break;
            }

            Vec3 pointBotTop = bot + (top - bot) * coverageBotTop;
            Vec3 pointMidTop = mid + (top - mid) * coverageMidTop;

            drawLine(renderer, (int) pointMidTop.x, y, (int) pointBotTop.x, y);
        }
    }
}