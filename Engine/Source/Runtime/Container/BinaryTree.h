#pragma once
#include "Container.h"
namespace Matrix
{
	namespace Container
	{
		template <class T>
		class MTXBinaryTreeNode
		{
		public:
			MTXBinaryTreeNode()
			{
				m_pParent = NULL;
				m_pLeft = NULL;
				m_pRight = NULL;
			};

			~MTXBinaryTreeNode()
			{
				m_pParent = NULL;
				m_pLeft = NULL;
				m_pRight = NULL;
			}
			template<class N>
			void PreProcess(N& Process)
			{
				Process(this);
				if (m_pLeft != NULL)
					m_pLeft->PreProcess(Process);
				if (m_pRight != NULL)
					m_pRight->PreProcess(Process);
			}
			template<class N>
			void PostProcess(N& Process)
			{
				if (m_pLeft != NULL)
					m_pLeft->PostProcess(Process);
				if (m_pRight != NULL)
					m_pRight->PostProcess(Process);
				Process(this);
			}
			template<class N>
			void MiddleProcess(N& Process)
			{
				if (m_pLeft != NULL)
					m_pLeft->MiddleProcess(Process);
				Process(this);
				if (m_pRight != NULL)
					m_pRight->MiddleProcess(Process);
			}

			inline bool IsLeft()
			{
				if (IsRoot())
					return false;
				if (m_pParent->m_pLeft == this)
					return true;
				return false;
			}

			inline bool IsRight()
			{
				if (IsRoot())
					return false;
				if (m_pParent->m_pRight == this)
					return true;
				return false;
			}

			inline bool IsRoot()
			{
				if (m_pParent == NULL)
					return true;
				return false;
			}

			unsigned int GetDepth()const //Root Depth = 1
			{
				unsigned int uiLeft = NULL;
				unsigned int uiRight = NULL;
				if (m_pLeft != NULL)
					uiLeft = m_pLeft->GetDepth();
				if (m_pRight != NULL)
					uiRight = m_pRight->GetDepth();
				if (uiLeft > uiRight)
					return uiLeft + 1;
				return uiRight + 1;
			}

			T Element;

			MTXBinaryTreeNode<T>* m_pParent;
			MTXBinaryTreeNode<T>* m_pLeft;
			MTXBinaryTreeNode<T>* m_pRight;
		};
		template <class T, class MTXMemManagerClass = DefaultContainerMemoryAllocator>
		class MTXDeleteProcess : public MContainer<MTXBinaryTreeNode<T>, MTXMemManagerClass>
		{
		public:
			MTXDeleteProcess()
			{

			}
			~MTXDeleteProcess() {}
			void  operator()(MTXBinaryTreeNode<T>* TreeNode)
			{
				Delete(TreeNode, 1);
			}
		};
		template <class T, class MTXMemManagerClass = DefaultContainerMemoryAllocator>
		class MTXBinaryTree : public MContainer<MTXBinaryTreeNode<T>, MTXMemManagerClass>
		{
		public:
			MTXBinaryTree()
			{
				m_uiNodeNum = 0;
				m_pRoot = NULL;
			}
			~MTXBinaryTree()
			{
				Clear();
			}
			template<class N>
			void PreProcess(N& Process)
			{
				if (m_pRoot)
				{
					m_pRoot->PreProcess(Process);
				}
			}
			template<class N>
			void PostProcess(N& Process)
			{
				if (m_pRoot)
				{
					m_pRoot->PostProcess(Process);
				}
			}
			template<class N>
			void MiddleProcess(N& Process)
			{
				if (m_pRoot)
				{
					m_pRoot->MiddleProcess(Process);
				}
			}
			void AddElement(const T& Element)
			{
				MTXBinaryTreeNode<T>* pCurrentNode = m_pRoot;

				if (m_pRoot == NULL)
				{
					MTXBinaryTreeNode<T>* pElem = New(1);
					new(pElem) MTXBinaryTreeNode<T>();
					pElem->Element = Element;
					m_pRoot = pElem;
					m_uiNodeNum++;
				}
				else
				{
					while (pCurrentNode != NULL)
					{
						if (Element < pCurrentNode->Element)
						{
							if (pCurrentNode->m_pLeft == NULL)
							{
								MTXBinaryTreeNode<T>* pElem = New(1);
								new(pElem) MTXBinaryTreeNode<T>();
								pElem->Element = Element;
								pCurrentNode->m_pLeft = pElem;
								pElem->m_pParent = pCurrentNode;
								pCurrentNode = NULL;
								m_uiNodeNum++;
							}
							else
							{
								pCurrentNode = pCurrentNode->m_pLeft;
							}

						}
						else if (Element > pCurrentNode->Element)
						{
							if (pCurrentNode->m_pRight == NULL)
							{
								MTXBinaryTreeNode<T>* pElem = New(1);
								new(pElem) MTXBinaryTreeNode<T>();
								pElem->Element = Element;

								pCurrentNode->m_pRight = pElem;
								pElem->m_pParent = pCurrentNode;
								pCurrentNode = NULL;
								m_uiNodeNum++;
							}
							else
							{
								pCurrentNode = pCurrentNode->m_pRight;
							}
						}
						else
						{
							pCurrentNode = NULL;
						}
					}
				}
			}

			inline unsigned int GetNodeNum()const
			{
				return m_uiNodeNum;
			}
			inline unsigned int GetDepth()const
			{
				if (!m_pRoot)
				{
					return 0;
				}
				else
				{
					return m_pRoot->GetDepth();
				}
			}
			bool Has(const T& Element)const
			{
				return (Find(Element) != NULL);
			}
			bool Erase(const T& Element)
			{
				MTXBinaryTreeNode<T>* pNode = (MTXBinaryTreeNode<T> *) Find(Element);
				if (!pNode)
					return false;
				if (!pNode->m_pLeft || !pNode->m_pRight)
					RemoveNotFull(pNode);
				else
					RemoveFull(pNode);
				m_uiNodeNum--;
				return true;
			}
			const MTXBinaryTreeNode<T>* Find(const T& Element) const
			{
				MTXBinaryTreeNode<T>* pCurNode = m_pRoot;
				while (pCurNode != NULL)
				{
					if (Element == pCurNode->Element)
						return pCurNode;
					if (Element < pCurNode->Element)
						pCurNode = pCurNode->m_pLeft;
					else
						pCurNode = pCurNode->m_pRight;
				}
				return NULL;
			}
			const T* FindElement(const T& Element) const
			{
				MTXBinaryTreeNode<T>* pCurNode = m_pRoot;
				while (pCurNode != NULL)
				{
					if (Element == pCurNode->Element)
						return &pCurNode->Element;
					if (Element < pCurNode->Element)
						pCurNode = pCurNode->m_pLeft;
					else
						pCurNode = pCurNode->m_pRight;
				}
				return NULL;
			}
		protected:
			void Clear()
			{
				MTXDeleteProcess<T, MTXMemManagerClass> t;
				PostProcess(t);
				m_pRoot = NULL;
				m_uiNodeNum = 0;
			}

			//Remove only has a child
			void RemoveNotFull(MTXBinaryTreeNode<T>* pNode)
			{
				MTXBinaryTreeNode<T>* pChildNode = NULL;
				if (pNode->m_pLeft != NULL)
				{
					pChildNode = pNode->m_pLeft;
				}
				if (pNode->m_pRight != NULL)
				{
					pChildNode = pNode->m_pRight;
				}

				if (pNode->IsRoot())
				{
					m_pRoot = pChildNode;
				}
				else
				{
					if (pNode->IsLeft())
					{
						pNode->m_pParent->m_pLeft = pChildNode;
					}
					else
					{
						pNode->m_pParent->m_pRight = pChildNode;
					}
				}

				if (pChildNode != NULL)
				{
					pChildNode->m_pParent = pNode->m_pParent;
				}

				Delete(pNode, 1);

			}
			MTXBinaryTreeNode<T>* FindLargestNode(MTXBinaryTreeNode<T>* pStartNode)
			{
				MTXBinaryTreeNode<T>* pNode = pStartNode;

				while (pNode->m_pRight != 0)
				{
					pNode = pNode->m_pRight;
				}
				return pNode;
			}
			//Remove only has two children
			void RemoveFull(MTXBinaryTreeNode<T>* pNode)
			{
				MTXBinaryTreeNode<T>* pLargestNode = FindLargestNode(pNode->m_pLeft);

				// There are two cases:
				if (pNode->m_pLeft == pLargestNode)
				{
					// The largest node is immediately to the left of the node to remove
					// so bypass pNode, and transfer pNode's right child.
					pLargestNode->m_pRight = pNode->m_pRight;
					pLargestNode->m_pRight->m_pParent = pLargestNode;
				}
				else
				{
					// the largest node is somewhere deeper in the tree.
					// shortened removeNotFull algorithm <G>:(notice how many assumptions can be made)
					pLargestNode->m_pParent->m_pRight = pLargestNode->m_pLeft;
					if (pLargestNode->m_pLeft != 0)
						pLargestNode->m_pLeft->m_pParent = pLargestNode->m_pParent;

					// now replace pNode with pLargestNode.
					pLargestNode->m_pLeft = pNode->m_pLeft;
					pLargestNode->m_pLeft->m_pParent = pLargestNode;
					pLargestNode->m_pRight = pNode->m_pRight;
					pLargestNode->m_pRight->m_pParent = pLargestNode;
				}

				if (pNode->IsRoot())
					m_pRoot = pLargestNode;
				else
				{
					if (pNode->IsLeft())
						pNode->m_pParent->m_pLeft = pLargestNode;
					else
						pNode->m_pParent->m_pRight = pLargestNode;
				}
				pLargestNode->m_pParent = pNode->m_pParent;
				Delete(pNode, 1);
			}
			MTXBinaryTreeNode<T>* m_pRoot;
			unsigned int m_uiNodeNum;
		};

	}
}


