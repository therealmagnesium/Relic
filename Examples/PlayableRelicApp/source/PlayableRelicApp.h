#include <Relic.h>

using namespace Relic;

// Make an app class that inherits from Relic::Application
class PlayableRelicApp : public Relic::Application
{
public:
    PlayableRelicApp(const WindowData& props);

    /* OnStart()
     *      - Called once, when the app is initialized
     *      - Used for initializing entities and other game objects
     */
    void OnStart() override;

    /* OnUpdate()
     *      - Called once per frame
     *      - Used for:
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

private:
    // A helper function to handle player movement
    void HandleMovement();

    // A helper function to spawn the player
    std::shared_ptr<Entity> SpawnPlayer();

    // A helper function to spawn entities
    std::shared_ptr<Entity> SpawnEntity(const Vector2& position, const Vector2& velocity, float radius, int points, const sf::Color& fill, const sf::Color& outline);

    // A helper function to spawn bullets
    void SpawnBullet(std::shared_ptr<Entity> entity, const Vector2& target);


private:
    std::shared_ptr<Entity> m_player;
    std::shared_ptr<Entity> m_octogon;
    std::shared_ptr<Entity> m_square;
};
