// Engine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

 
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <stack>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"





enum class ComponentType :uint32_t
{
	TRANSFORM,
	MESH,
	CAMERA,
	COUNT 
};

struct Handle
{
	uint32_t id;  //        31 -- handle type -- 24| 23 --  array index --- 0
};

Handle create_handle(ComponentType t, uint32_t idx)
{
	return   { uint32_t(t) << 24 | idx };
}

inline uint32_t get_handle_resource_index(const Handle handle)
{
	return handle.id & 0xFFFFFF;
}
inline ComponentType get_handle_resource_type(const Handle handle)
{
	return  (ComponentType)(handle.id >> 24);
}

void handle_decode(const Handle& handle, ComponentType& t, uint32_t& idx)
{
	t   = get_handle_resource_type(handle);
	idx = get_handle_resource_index(handle);
}


struct Transform
{
	Handle    parent = {0};
	const ComponentType type = ComponentType::TRANSFORM;
	glm::mat4 model;
	glm::mat4 world;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale = glm::vec3(1.0f);
	bool is_dirty = true;
#ifdef _DEBUG
	std::string name;
#endif // _DEBUG

};



struct SceneNode
{

};
std::vector<Transform> transforms;

 
Handle create_transform_component(const char* name)
{
	transforms.emplace_back();
	transforms[(uint32_t)transforms.size() - 1].name = name;
	return create_handle(ComponentType::TRANSFORM, (uint32_t)transforms.size());//we start from non zero index to prevent valid handle with value of zero
}

Transform* get_transform_component(Handle handle)
{
	if (handle.id == 0)
	{
		return nullptr;
	}
	assert(handle.id);
	const uint32_t idx = get_handle_resource_index(handle);
	assert(idx <= transforms.size());
	return &transforms[idx - 1]; //we must - 1 as we add 1 to the index of new item in comp array so that the handle value can never be equal 0

}

void add_child(Handle parent, Handle child)
{
	//Transform* parent_node = get_transform_component(parent);
	Transform* child_node = get_transform_component(child);
	child_node->parent = parent;
}

void CalculateLocalTransform(Transform* currentT)
{
	 
	currentT->model = glm::translate(glm::mat4(1.0f), currentT->position);
	glm::quat rotTemp;
	glm::mat4 rotMatrix = glm::mat4_cast(
		glm::rotate(rotTemp, currentT->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)) * 
		glm::rotate(rotTemp, currentT->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(rotTemp, currentT->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f))
	);
	currentT->model *= rotMatrix;
	currentT->model = glm::scale(currentT->model, currentT->scale);
	//currentT->model = glm::rotate()
}

void CalculateTransform(Transform* currentT,Transform* parentT)
{
	CalculateLocalTransform(currentT);
 
	currentT->world = parentT? parentT->world * currentT->model : currentT->model;
}
std::vector<Transform*> traverseStack;
void traverse_transforms()
{
	
	
	for (size_t i = 0; i < transforms.size(); i++)
	{
		uint32_t topDirtyIdx = 0;
		Transform* currentTransform = &transforms[i];
		do {

			traverseStack.push_back(currentTransform);
			topDirtyIdx = currentTransform->is_dirty ? (uint32_t)traverseStack.size() - 1 : topDirtyIdx;
			currentTransform = get_transform_component(currentTransform->parent);

		} while (currentTransform);
		
		
		//go down
		
		printf("---------- Root start ------------\n");
		//we must find the parent of the first dirty node,otherwise if parent node
		//has been updated in another sub-tree this node won't know anything about it 
		//because it becomes the first one to update from
		Transform* parentWorld = get_transform_component(traverseStack[topDirtyIdx]->parent);
		for (int i = topDirtyIdx; i >= 0; --i)
		{
			Transform* thisTransform = traverseStack[i];
			printf("node %s\n", thisTransform->name.c_str());
			CalculateTransform(thisTransform, parentWorld);
			thisTransform->is_dirty = false;
			parentWorld = thisTransform;
		}
		traverseStack.clear();

		/*while (!traverseStack.empty())
		{
			Transform* thisTransform = traverseStack.top();
			traverseStack.pop();
			printf("node %s\n", thisTransform->name.c_str());
			CalculateTransform(thisTransform, parentWorld);
			thisTransform->is_dirty = false;
			parentWorld = thisTransform;
		}*/
		printf("---------- Root end ------------\n");

	}
}

class SceneObject
{
	static uint32_t globalId;
	uint32_t id; //entity unique id
	Handle components[(uint32_t)ComponentType::COUNT];

public:

	void AddComponent(const ComponentType cType,Handle component)
	{
			components[(uint32_t)cType] = component;
	}
	SceneObject()
	{
		memset(components, 0, sizeof(components));	
		AddComponent(ComponentType::TRANSFORM, create_transform_component(""));
	}
};
int main()
{
	Handle transform_root_handle = create_transform_component("root_node");
	Handle transform_child_to_root1_handle = create_transform_component("child_to_root_1");
	Handle transform_child_to_root2_handle = create_transform_component("child_to_root_2");
	Handle transform_child_to_child_to_root1_handle = create_transform_component("child_to_child_to_root_1");

	Transform* trm1 = get_transform_component(transform_child_to_root1_handle);

	add_child(transform_root_handle, transform_child_to_root1_handle);
	add_child(transform_root_handle, transform_child_to_root2_handle);
	add_child(transform_child_to_root1_handle, transform_child_to_child_to_root1_handle);

	traverse_transforms();

	return EXIT_SUCCESS;
}

 
