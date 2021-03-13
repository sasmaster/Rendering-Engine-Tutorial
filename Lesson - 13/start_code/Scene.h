#ifndef SGE_SCENE_H
#define SGE_SCENE_H

#include "Engine.h"
#include "SceneNode.h"
#include <vector>
namespace sge
{
	class MeshNode;
	class CameraNode;
	class Scene
	{
		CameraNode* mCurrentCamera;
		SceneNode mRootNode;

		bool mSceneDirty;

		std::vector<SceneNode*> mSceneNodes;
		std::vector<MeshNode*>  mRenderableNodes;
		void SetScene(SceneNode* node);
	public:

		SGE_DISABLE_COPY_ASSIGN(Scene)

		Scene();

		template<typename T,typename ...Args>
		T* CreateSceneNode(Args&&... args)
		{
			T* newSceneNode = new T(std::forward<Args>(args)...);
			SetScene(newSceneNode);
			mSceneNodes.push_back(newSceneNode);
		
			return newSceneNode;
		}

		void AddNode(SceneNode* node);

		void SetCurrentCamera(CameraNode* camera);

		const CameraNode* GetCurrentCamera()const
		{
			return mCurrentCamera;
		}

		void RemoveNode(SceneNode* node);

		void Update();

		const std::vector<MeshNode*>& GetRenderableNodes()const
		{
			return mRenderableNodes;
		}

		void SetDirty()
		{
			mSceneDirty = true;
		}

		void GatherRenderableNodes();

		~Scene();

	private:

	};

	

}

#endif // !SGE_SCENE_H
