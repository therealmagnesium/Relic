#include "MainMenuScene.h"
#include "GameScene.h"

MainMenuScene::MainMenuScene(Application* app) :
    Scene(app)
{
    // Setup the scene
    CreateBackground();
    SpawnLogo();
    SpawnStartText();
    SpawnAllEntities();
    SetupAndPlayAudio();
}

void MainMenuScene::OnUpdate(float dt)
{
    // Close the game if the escape key was pressed
    if (Input::IsKeyPressed(Key::Escape))
        m_app->Close();

    // Switch to the game scene if the space key was presed
    if (Input::IsKeyPressed(Key::Space))
        m_app->ChangeScene("game", std::make_shared<GameScene>(m_app), true);

    RotateAllEntities();
}

void MainMenuScene::OnEnd()
{
    // Stop the main menu music
    RL_INFO("Ending scene [{}]", m_app->GetCurrentScene());
    m_backgroundMusic->GetComponent<AudioSource>().audio.Stop();
}

void MainMenuScene::CreateBackground()
{
    // Give the background a transform and an image to render
    std::shared_ptr<Entity> bg = m_entityManager.AddEntity("bg");
    bg->AddComponent<Transform>();
    bg->AddComponent<SpriteRenderer>(m_app->GetAssets()->GetTexture("main_menu_bg"));
}

void MainMenuScene::SetupAndPlayAudio()
{
    // Play the main menu music and enable looping
    m_backgroundMusic = m_entityManager.AddEntity("music");
    m_backgroundMusic->AddComponent<AudioSource>(m_app->GetAssets()->GetMusicPath("menu"));
    m_backgroundMusic->GetComponent<AudioSource>().audio.SetStartOffset(0.f);
    m_backgroundMusic->GetComponent<AudioSource>().audio.SetLoop(true);
    m_backgroundMusic->GetComponent<AudioSource>().audio.Play();
}

void MainMenuScene::SpawnLogo()
{
    // Give the logo a transform and an image, then set the scale and origin 
    std::shared_ptr<Entity> logo = m_entityManager.AddEntity("menu_token");
    logo->AddComponent<Transform>(Vector2(m_app->GetWindowWidth()/2.f, 500.f));
    logo->AddComponent<SpriteRenderer>(m_app->GetAssets()->GetTexture("relic_logo"));
    auto& sr = logo->GetComponent<SpriteRenderer>().sprite;
    sr.SetOrigin(sr.GetSize().x/2.f, sr.GetSize().y/2.f);
    sr.SetScale(0.7f, 0.7f);
}

void MainMenuScene::SpawnStartText()
{
    // Give the start text a transform and a message, then set the origin
    std::shared_ptr<Entity> startText = m_entityManager.AddEntity("menu_token");
    startText->AddComponent<Transform>(Vector2(m_app->GetWindowWidth()/2.f, 
                m_app->GetWindowHeight()/1.5f));
    startText->AddComponent<Text>(m_app->GetAssets()->GetFont("main"), "Press space to play game", 40);
    auto& text = startText->GetComponent<Text>().text;
    text.SetOrigin(text.GetWidth()/2.f, text.GetHeight()/2.f);
}

void MainMenuScene::SpawnAllEntities()
{
    // Spawn some entities on the screen
    SpawnEntity(Vector2(400.f, 400.f));
    SpawnEntity(Vector2(m_app->GetWindowWidth() - 400.f, 400.f)); 
}
void MainMenuScene::SpawnEntity(const Vector2& pos)
{
    // Spawn a shape, center the origin and set the position
    std::shared_ptr<Entity> entity = m_entityManager.AddEntity("entity");
    entity->AddComponent<Shape>(64.f);
    auto& shape = entity->GetComponent<Shape>().shape;
    shape.SetOutlineColor(0x0FA3B1FF);
    shape.SetOrigin(shape.GetRadius(), shape.GetRadius()); 
    entity->AddComponent<Transform>(pos);
}

void MainMenuScene::RotateAllEntities()
{
    // Rotate all entities with the tag 'entity'
    for (auto& e : m_entityManager.GetEntities("entity"))
        e->GetComponent<Transform>().angle += 2.f;
}
