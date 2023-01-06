#pragma once
#include <Config.h>
#include <memory>
#include <vector>
#include <functional>

SOLAR_BEGIN
template<class T>
class TreeNode
{
    using IndexType = typename std::vector<TreeNode>::size_type;
    using RefType = T&;
    using ConstRefType = const T&;
protected:
    std::shared_ptr<TreeNode> mParent;
    std::vector<std::shared_ptr<TreeNode>> mChilds;

    T mData;
public:

    TreeNode() : mData(T()){}
    TreeNode(ConstRefType data) : mData(data){}

    TreeNode& PushChild(const TreeNode& Node)
    {
        TreeNode& ref = const_cast<TreeNode&>(Node);
        ref.mParent = std::make_shared<TreeNode>(*this);
        mChilds.push_back(std::make_shared<TreeNode>(ref));
        return *mChilds[mChilds.size() - 1];
    }
    
    void PopChild(const TreeNode& node)
    {
        mChilds.pop_back();
    }

    void SetParent(const TreeNode& Parent) { mParent = std::make_shared<TreeNode>(Parent);}
    NODISCARD const std::vector<std::shared_ptr<TreeNode>>& Childs() const { return mChilds; }
    NODISCARD std::vector<std::shared_ptr<TreeNode>>& Childs() { return mChilds; }

    NODISCARD const TreeNode& GetParent() const { return *mParent; }
    NODISCARD TreeNode& GetParent() { return *mParent; }
    
    NODISCARD const TreeNode& GetChildAt(IndexType index) const { return *mChilds[index]; }
    NODISCARD TreeNode& GetChildAt(IndexType index) { return *mChilds[index]; }

    NODISCARD RefType Data() { return mData; }
    NODISCARD ConstRefType Data() const { return mData; }
};


template<class T, class TreeNodeBase = TreeNode<T>>
class Tree
{
private:
    TreeNodeBase mRootNode;


public:
    Tree() { mRootNode = TreeNodeBase();}
    Tree(const TreeNodeBase& Init) { mRootNode = Init;}
    ~Tree(){}
    
    NODISCARD const TreeNodeBase& GetRoot() const { return mRootNode; }
    TreeNodeBase& GetRoot() { return mRootNode; }

    void ForEach(const std::function<void(TreeNodeBase& Node)>& func)
    {
        
        for(size_t i = 0; i < GetRoot().Childs().size(); i++)
        {
            TreeNodeBase& Child = GetRoot().GetChildAt(i);
            func(Child);
            for(size_t j = 0; j < Child.Childs().size(); j++)
            {
                TreeNodeBase& ChildChild = Child.GetChildAt(j);
                func(ChildChild);
            }
        }
    }
};
SOLAR_END