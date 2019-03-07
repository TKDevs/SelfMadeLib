#ifndef QUADTREE_H
#define QUADTREE_H

#include <iostream>
#include <fstream>
namespace qt {
	//-----------------------------------------------------------------------------------
	class Point {
	public:
		Point(float x, float y) : x_(x), y_(y) {}

		//get functions
		float getX() { return x_; }
		float getY() { return y_; }
		//set functions
		void setX(float x) { x_ = x; }
		void setY(float y) { y_ = y; }
	private:
		float x_;
		float y_;
	};
	//-----------------------------------------------------------------------------------
	class Rectangle {
	public:
		Rectangle(float x, float y, float width, float height) : x_(x), y_(y), width_(width), height_(height) {}

		//returns a boolean if the point is in the rectangle
		bool contains(Point* point) {
			return (point->getX() > x_ &&
				point->getX() < x_ + width_ &&
				point->getY() > y_ &&
				point->getY() < y_ + height_);
		}

		//returns a boolean if two rectangle intersect
		bool intersects(Rectangle* area) {
			return !(area->getX() > x_ + width_ ||
				area->getX() + area->getWidth() < x_ ||
				area->getY() > y_ + height_ ||
				area->getY() + area->getHeight() < y_);
		}

		//get functions
		float getX() { return x_; }
		float getY() { return y_; }
		float getWidth() { return width_; }
		float getHeight() { return height_; }
		//set functions
		void setX(float x) { x_ = x; }
		void setY(float y) { y_ = y; }
		void setWidth(float width) { width_ = width; }
		void setHeight(float height) { height_ = height; }
	private:
		float x_;
		float y_;
		float width_;
		float height_;
	};
	//-----------------------------------------------------------------------------------
	class Circle {
	public:
		Circle(float x, float y, float r) : x_(x), y_(y), r_(r) {};

		//returns a boolean if the point is in the rectangle or not
		bool contains(Point* point) { return ((sqrt((point->getX() - x_)*(point->getX() - x_) + (point->getY() - y_)*(point->getY() - y_))) <= r_); }

		//returns a boolean if a circle and a rectangle intersect
		bool intersects(Rectangle* area) {
			float x_distance = abs((area->getX() + area->getWidth() / 2.f) - x_);
			float y_distance = abs((area->getY() + area->getHeight() / 2.f) - y_);
			float edges = (x_distance - area->getWidth() / 2.f)*(x_distance - area->getWidth() / 2.f) + (y_distance - area->getHeight() / 2.f)* (y_distance - area->getHeight() / 2.f);

			if (x_distance > (r_ + area->getWidth() / 2.f) || y_distance > (r_ + area->getHeight() / 2.f)) { return false; }
			if (x_distance <= (area->getWidth() / 2.f) || y_distance <= (area->getHeight() / 2.f)) { return true; }
			return(edges <= r_ * r_);
		}

		//get functions
		float getX() { return x_; }
		float getY() { return y_; }
		float getR() { return r_; }
		//set functions
		void setX(float x) { x_ = x; }
		void setY(float y) { y_ = y; }
		void setR(float r) { r_ = r; }
	private:
		float x_;
		float y_;
		float r_;
	};
	//-----------------------------------------------------------------------------------
	class Quadtree {
	public:
		Quadtree(Rectangle boundary, int capacity) :boundary_(boundary), capacity_(capacity) {}

		//insert a point into the quadtree
		void insert(Point* point) {
			if (!boundary_.contains(point)) { return; }
			else {
				if (points_.size() < capacity_) { points_.push_back(point); }
				else {
					if (!divided_) { subdivide(); }
					top_left_->insert(point);
					top_right_->insert(point);
					bottom_left_->insert(point);
					bottom_right_->insert(point);
				}
			}
		}

		//query a specific area in the quadtree (Rectangle)
		std::vector<Point*> query(Rectangle* area) {
			std::vector<Point*> found;
			if (!area->intersects(&boundary_)) { return found; }
			else {
				for (Point* p : points_) {
					if (area->contains(p)) { found.push_back(p); }
				}
				if (divided_) {
					top_left_->query(area, &found);
					top_right_->query(area, &found);
					bottom_left_->query(area, &found);
					bottom_right_->query(area, &found);
				}
				return found;
			}
		}
		//query a specific area in the quadtree (Circle)
		std::vector<Point*> query(Circle* area) {
			std::vector<Point*> found;
			if (!area->intersects(&boundary_)) { return found; }
			else {
				for (Point* p : points_) {
					if (area->contains(p)) { found.push_back(p); }
				}
				if (divided_) {
					top_left_->query(area, &found);
					top_right_->query(area, &found);
					bottom_left_->query(area, &found);
					bottom_right_->query(area, &found);
				}
				return found;
			}
		}

		//log the quadtree
		void log() {
			int generation = 1;
			std::ofstream file;
			file.open("QuadtreeLog.txt", std::fstream::out);
			if (file.is_open()) {
				file << "Quadtree generation: " << generation << " from " << boundary_.getX() << "|" << boundary_.getY() << " to "
					<< boundary_.getX() + boundary_.getWidth() << "|" << boundary_.getY() + boundary_.getHeight() << "\n   ";
				if (points_.size() == 0) { file << "Empty" << '\n' << '\n'; }
				else {
					for (Point* p : points_) { file << "Point " << " X:" << p->getX() << "    Y:" << p->getY() << "\n   "; }
					file << '\n';
					file.close();
					if (divided_) {
						top_left_->logSubsections(generation);
						top_right_->logSubsections(generation);
						bottom_left_->logSubsections(generation);
						bottom_right_->logSubsections(generation);
					}
				}
			}
		}

		//shows the grid of the quadtree
		void show(sf::RenderWindow* window) {
			sf::RectangleShape rect(sf::Vector2f(boundary_.getWidth(), boundary_.getHeight()));
			rect.setPosition(boundary_.getX(), boundary_.getY());
			rect.setOutlineThickness(2);
			rect.setOutlineColor(sf::Color(255, 255, 255));
			rect.setFillColor(sf::Color(0, 0, 0));
			window->draw(rect);

			if (divided_) {
				top_left_->show(window);
				top_right_->show(window);
				bottom_left_->show(window);
				bottom_right_->show(window);
			}
		}

		void deleteQuadtree() {
			if (divided_) {
				top_left_->deleteQuadtree();
				top_right_->deleteQuadtree();
				bottom_left_->deleteQuadtree();
				bottom_right_->deleteQuadtree();

				delete this;
			}
		}

		//get functions
		int getCapacity() { return capacity_; }
		bool getDivided() { return divided_; }
		Rectangle getBoundary() {return boundary_; }
	private:
		void subdivide() {
			divided_ = true;
			top_left_ = new Quadtree(Rectangle(boundary_.getX(), boundary_.getY(), boundary_.getWidth() / 2, boundary_.getHeight() / 2), capacity_);
			top_right_ = new Quadtree(Rectangle(boundary_.getX() + boundary_.getWidth() / 2, boundary_.getY(), boundary_.getWidth() / 2, boundary_.getHeight() / 2), capacity_);
			bottom_left_ = new Quadtree(Rectangle(boundary_.getX(), boundary_.getY() + boundary_.getWidth() / 2, boundary_.getWidth() / 2, boundary_.getHeight() / 2), capacity_);
			bottom_right_ = new Quadtree(Rectangle(boundary_.getX() + boundary_.getWidth() / 2, boundary_.getY() + boundary_.getHeight() / 2, boundary_.getWidth() / 2, boundary_.getHeight() / 2), capacity_);
		}
		void logSubsections(int generation) {
			generation++;
			std::ofstream file;
			file.open("QuadtreeLog.txt", std::fstream::out | std::fstream::app);
			if (file.is_open()) {
				for (int i = 0; i < generation - 1; i++) { file << "  "; }
				file << "Quadtree generation: " << generation << " from " << boundary_.getX() << "|" << boundary_.getY() << " to "
					<< boundary_.getX() + boundary_.getWidth() << "|" << boundary_.getY() + boundary_.getHeight() << "\n";
				for (int i = 0; i < generation - 1; i++) { file << "  "; }
				if (points_.size() == 0) { file << "Empty" << '\n' << '\n'; }
				else {
					for (Point* p : points_) {
						file << "Point " << " X:" << p->getX() << "    Y:" << p->getY() << "\n";
						for (int i = 0; i < generation - 1; i++) { file << "  "; }
					}
					file << '\n';
					file.close();
					if (divided_) {
						top_left_->logSubsections(generation);
						top_right_->logSubsections(generation);
						bottom_left_->logSubsections(generation);
						bottom_right_->logSubsections(generation);
					}
				}
			}
		}
		void query(Rectangle* area, std::vector<Point*>* found) {
			if (!area->intersects(&boundary_)) { return; }
			else {
				for (Point* p : points_) {
					if (area->contains(p)) { found->push_back(p); }
				}
				if (divided_) {
					top_left_->query(area, found);
					top_right_->query(area, found);
					bottom_left_->query(area, found);
					bottom_right_->query(area, found);
				}
				return;
			}
		}
		void query(Circle* area, std::vector<Point*>* found) {
			if (!area->intersects(&boundary_)) { return; }
			else {
				for (Point* p : points_) {
					if (area->contains(p)) { found->push_back(p); }
				}
				if (divided_) {
					top_left_->query(area, found);
					top_right_->query(area, found);
					bottom_left_->query(area, found);
					bottom_right_->query(area, found);
				}
				return;
			}
		}

		Rectangle boundary_;
		int capacity_;
		bool divided_;
		std::vector<Point*> points_;
		Quadtree* top_left_;
		Quadtree* top_right_;
		Quadtree* bottom_left_;
		Quadtree* bottom_right_;
	};
}
#endif