#include "Scene.h"
#include "SceneNode.h"
#include <stack> 
namespace sge 
{

	Scene::Scene()
		:mSceneDirty(true)
	{
		mRootNode.mScene = this;
	}

	void Scene::AddNode(SceneNode* node)
	{
		mRootNode.AddNode(node);
	}

	void Scene::RemoveNode(SceneNode* node)
	{
		mRootNode.RemoveNode(node);
	}

	void Scene::Update()
	{
		GatherRenderableNodes();
		mRootNode.UpdateTransform(glm::mat4(1.0f), false);
	}

	void Scene::SetScene(SceneNode* node)
	{
		node->mScene = this;
	}

	void Scene::SetCurrentCamera(CameraNode* camera)
	{
		mCurrentCamera = camera;
	}

	void Scene::GatherRenderableNodes()
	{
		if (mSceneDirty)
		{
			mRenderableNodes.clear();

			std::stack<SceneNode*> nodes;
			nodes.push(&mRootNode);

			while (!nodes.empty())
			{

				auto currentNode = nodes.top();
				const auto& children = currentNode->GetChildren();
				nodes.pop();
				for (auto i = children.cbegin(); i != children.cend();i++)
				{
					nodes.push(*i);
				}

				if (currentNode->GetNodeType() == NodeType::MESH_NODE)
				{
					mRenderableNodes.push_back((MeshNode*)currentNode);
				}
			}

			mSceneDirty = false;

		}
	}


	Scene::~Scene()
	{
	}

}