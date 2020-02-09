#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleBeachTrack.h"
#include "SDL.h"
#include "ModuleAudio.h"



// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer (bool start_enabled):
Module (start_enabled)
{
  //FORWARD 

  // idle animation (stopped movement with no hill)
  idle.frames.push_back (
			  {
			  0, 44, 90, 41});

  //idle (stopped uphill)
  idleUp.frames.push_back (
			    {
			    0, 0, 90, 44});

  // forward movement with no hill
  forward.frames.push_back (
			     {
			     0, 44, 90, 41});
  forward.frames.push_back (
			     {
			     92, 44, 90, 41});
  forward.speed = 0.2f;

  // move upwards (forward but uphill)
  forwardUp.frames.push_back (
			       {
			       0, 0, 90, 44});
  forwardUp.frames.push_back (
			       {
			       92, 0, 90, 44});
  forwardUp.speed = 0.2f;

  //move downwards (forward but downhill)
  forwardDown.frames.push_back (
				 {
				 0, 85, 90, 36});
  //forwardDown.frames.push_back({ 92, 0, 90, 44 });
  forwardDown.speed = 0.2f;

  //LEFT

  //idle left (no movement but turned left)
  idleLeft.frames.push_back (
			      {
			      656, 165, 84, 41});

  //idle left (going uphill)
  idleUpLeft.frames.push_back (
				{
				653, 121, 86, 44});

  //turn left (no hill)
  left.frames.push_back (
			  {
			  656, 165, 84, 41});
  left.frames.push_back (
			  {
			  564, 165, 84, 41});
  left.speed = 0.2f;

  //turn left (uphill)
  leftUp.frames.push_back (
			    {
			    653, 121, 86, 44});
  leftUp.frames.push_back (
			    {
			    561, 121, 86, 44});
  leftUp.speed = 0.2f;

  //RIGHT

  //idle right (no movement but turned right)
  idleRight.frames.push_back (
			       {
			       0, 165, 84, 41});

  //idle right (going uphill)
  idleUpRight.frames.push_back (
				 {
				 0, 121, 84, 44});

  //turn right (no hill)
  right.frames.push_back (
			   {
			   0, 165, 84, 41});
  right.frames.push_back (
			   {
			   92, 165, 84, 41});
  right.speed = 0.2f;

  //turn right (uphill)
  rightUp.frames.push_back (
			     {
			     0, 121, 84, 44});
  rightUp.frames.push_back (
			     {
			     92, 121, 84, 44});
  rightUp.speed = 0.2f;


}

ModulePlayer::~ModulePlayer ()
{

}

// Load assets
bool
ModulePlayer::Start ()
{
  LOG ("Loading player");

  graphics = App->textures->Load ("resources/Sprites/ferrari.png");
  crash = App->audio->LoadFx ("resources/Music/SmallCrash.ogg");
  speed = App->audio->LoadFx ("resources/Music/Speed.ogg");

  return true;
}

// Unload assets
bool
ModulePlayer::CleanUp ()
{
  LOG ("Unloading player");

  App->textures->Unload (graphics);

  return true;
}

void const
ModulePlayer::DetectCollision (const SDL_Rect r)
{
  if (!
      (collider.x > r.x + r.w || collider.x + collider.w < r.x
       || collider.y > r.y + r.h || collider.y + collider.h < r.y))
    {
      App->audio->PlayFx (crash, 0);
      App->beach_track->playerZ = 0;
      App->beach_track->speed = 0;
    }

}

// Update
update_status
ModulePlayer::Update ()
{




  collider = { SCREEN_WIDTH / 2 - carState->GetCurrentFrame ().w + 40,
    SCREEN_HEIGHT - 50, (carState->GetCurrentFrame ().w - 40) * 2, 50
  };

  return UPDATE_CONTINUE;
}
