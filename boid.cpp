#include "boid.h"
#include <math.h>

 void normalize(vector<double> &dir)
{
  double norma;
  norma = sqrt(pow(dir[0],2) + pow(dir[1],2) + pow(dir[2],2));
  dir[0] /= norma;
  dir[1] /= norma;
  dir[2] /= norma;
}

Boid::Boid(double x, double y,double z, double width, double height)
{
  srand(time(NULL));

  position = Vector2d<double>(x, y, z);

  random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<double> dist(-5.0, 5.0);

  velocity = Vector2d<double>(dist(mt),dist(mt),dist(mt));

  acceleration = Vector2d<double>(dist(mt)/20,dist(mt)/20,dist(mt)/20);

  this->max_force = 0.0001;
  this->max_speed = 0.7;
  this->perception = 5;

  this->width = width;
  this->height = height;

  //normalize(direction);
}



void Boid::draw()
{
  /*float pitch, yaw, roll;

	// Draw boid

	glPushMatrix();

		// translate to the particle position
		// Pos.Translate();
		glTranslatef( position[0], position[1], position[2] );

		//Convert from radians to degrees
	  pitch = direction[0] * 57.295779524;
		yaw = direction[1] * 57.295779524;
		roll = direction[2] * 57.295779524;

    direction[0] = -atan(speed[1]/sqrt(speed[0]*speed[0] + speed[2]*speed[2]));

    // Yaw
  direction[1] = atan2(speed[0], speed[2]);



		// Rotate the boid appropriately
		glRotatef(pitch, 1.0, 0.0, 0.0);
		glRotatef(yaw, 0.0, cos(direction[0]), - sin(direction[0]));
		glRotatef(roll, 0.0, 0.0, 1.0);

		glScalef(1.0, 0.3, 0.3);
		glutSolidCone(1, 2, 8, 2);

	glPopMatrix();

  position[0] += speed[0]*1;
  position[1] += speed[1]*1;
  position[2] += speed[2]*1;



  cout << "d: " <<  direction[0] << " " <<  direction[1] << " " << direction[2] << "\n";
  cout << position[0] << " " << position[1] <<  " " << position[2] << "\n";*/


  // glPointSize(5.0);
  // glBegin(GL_POINTS);
  //     glColor3f(0.0,1.0,0.0);
  //     glVertex2f(position.x,position.y);
  // glEnd();




  glPushMatrix();
  glRotated(30,velocity.x,velocity.y,velocity.z);
  glBegin(GL_TRIANGLES);
  double tam = 0.3;
  glColor3f(0.5,0,0);

  glVertex2f(position.x,position.y+tam);
  glVertex2f(position.x-tam,position.y-tam);
  glVertex2f(position.x+tam,position.y-tam);

  glEnd();
  glPopMatrix();

}


void Boid::update()
{
  position = position + velocity;
  velocity = velocity + acceleration;

  if(velocity.norma() > max_speed)
    velocity = velocity /(velocity.norma()* max_speed);
  acceleration.zero();
}

void Boid::edges()
{
    double negative_width = (-1)*width;
    double negative_height = (-1)*height;
    if (position.x > width)
      position.x = negative_width;
    else if (position.x < negative_width)
      position.x = width;

    if (position.y > height)
      position.y = negative_height;
    else if (position.y < negative_height)
      position.y = height;

    if (position.z > height)
      position.z = negative_height;
    else if (position.z < negative_height)
      position.z = height;

}

void Boid::behaviour(vector<Boid *> flock)
{
    Vector2d<double> alignments,cohesions,separations;
    alignments = this->align(flock);
    cohesions = this->cohesion(flock);
    separations = this->separation(flock);

    this->acceleration = this->acceleration + alignments;
    this->acceleration = this->acceleration + cohesions;
    this->acceleration = this->acceleration + separations;
}

Vector2d<double> Boid::align(vector<Boid *> flock)
{
  Vector2d<double> steering;
  steering.zero();

  double total =0;

  Vector2d<double> avg_vector;
  avg_vector.zero();

  for(int i=0;i < flock.size();i++)
  {
    if((flock[i]->position - this->position).norma() < this->perception)
    {
      avg_vector = avg_vector + flock[i]->velocity;
      total += 1;
    }
  }
  if(total > 0)
  {
    avg_vector = avg_vector/total;
    //avg_vector = Vector(*avg_vector)
    avg_vector = (avg_vector / avg_vector.norma()) * this->max_speed;
    steering = avg_vector - this->velocity;
  }

  return steering;
}

Vector2d<double> Boid::cohesion(vector<Boid *> flock)
{
  Vector2d<double> steering;
  steering.zero();

  double total = 0;

  Vector2d<double> center_of_mass;
  center_of_mass.zero();

  for(int i=0;i < flock.size();i++)
  {
    if((flock[i]->position - this->position).norma() < this->perception)
    {
      center_of_mass = flock[i]->position;
      total += 1;
    }
  }
  if(total > 0)
  {
    center_of_mass = center_of_mass/total;
    //center_of_mass = Vector(*center_of_mass)
    Vector2d<double> vec_to_com = center_of_mass - this->position;

    if(vec_to_com.norma() > 0)
    {
      vec_to_com = (vec_to_com / vec_to_com.norma()) * this->max_speed;
    }
    steering = vec_to_com - this->velocity;
    if(steering.norma() > max_force)
    {
      steering = (steering / steering.norma()) * this->max_force;
    }
  }

  return steering;
}

Vector2d<double> Boid::separation(vector<Boid *> flock)
{
  Vector2d<double> steering;
  steering.zero();

  double total = 0;

  Vector2d<double> avg_vector;
  avg_vector.zero();

  for(int i=0;i < flock.size();i++)
  {
    double distance = (flock[i]->position - this->position).norma();
    if(this->position != flock[i]->position and distance < this->perception)
    {
      Vector2d<double> diff;
      diff = this->position - flock[i]->position;
      diff = diff /distance;
      avg_vector = avg_vector + diff;
      total += 1;
    }
  }
  if(total > 0)
  {
    avg_vector = avg_vector/total;
    //avg_vector = Vector(*avg_vector)
    if(steering.norma() > 0)
    {
      avg_vector = (avg_vector / steering.norma()) * this->max_speed;
    }
    steering = avg_vector - this->velocity;
    if(steering.norma() > max_force)
    {
      steering = (steering / steering.norma()) * this->max_force;
    }
  }

  return steering;
}
