#include "Application.h"

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace Relic
{
    Application::Application(const ApplicationProperties& props) :
        m_properties(props)
    {
        Init();
    }

    Application::~Application()
    {
        Shutdown();
    }

    void Application::Init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || !IMG_Init(IMG_INIT_PNG))
        {
            printf("Failed to init sdl2: %s\n", SDL_GetError());
            return;
        }

        m_windowHandle = SDL_CreateWindow(m_properties.name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                            m_properties.width, m_properties.height, 0);
        if (!m_windowHandle)
        {
            printf("Failed to make window: %s\n", SDL_GetError());
            return;
        }

        m_renderer = SDL_CreateRenderer(m_windowHandle, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!m_renderer)
        {
            printf("Failed to make renderer: %s\n", SDL_GetError());
            return;
        }

        SDL_SetRenderDrawColor(m_renderer, 0x00, 0x22, 077, 0xFF);
    }

    void Application::Shutdown()
    {
        SDL_DestroyWindow(m_windowHandle);
        SDL_DestroyRenderer(m_renderer);
        IMG_Quit();
        SDL_Quit();
    }

    void Application::Run()
    {
        m_running = true;
        
        while (m_running)
        {
            SDL_Event event;
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT) Close();

            SDL_RenderClear(m_renderer);
            SDL_RenderPresent(m_renderer);
        }
    }

    void Application::Close()
    {
        m_running = false;
    } 
}