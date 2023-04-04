#include <Relic.h>

// Make an app class that inherits from Relic::Application
class BasicRelicApp : public Relic::Application
{
public:
        // Simple constructor for the app
        BasicRelicApp(const Relic::ApplicationProperties& props);

        /* OnStart()
         *      - Called once, when the app is initialized
         *      - Used for initializing entities and other game objects
         */
        void OnStart() override;

        /* OnUpdate()
         *      - Called once per frame
         *      - Used for:
         *              - Handeling input
         *              - Collisions / physics
         *              - Movement
         */
        void OnUpdate() override;

        /* OnRender()
         *      - Called once per frame, after OnUpdate()
         *      - Used for:
         *              - Rendering enteties
         *              - Dynamic graphic properties
         */
        void OnRender() override;
};
