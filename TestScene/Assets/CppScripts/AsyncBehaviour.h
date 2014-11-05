#ifndef AsyncBehaviour_h
#define AsyncBehaviour_h
#include "CppBehaviour.h"
#include <vector>

class AsyncBehaviour;
typedef uint32_t EntityHandle;

class AsyncBehaviourManager : public CppBehaviour
{
typedef CppBehaviour super;
public:
    typedef std::vector<AsyncBehaviour*> EntityCont;
    typedef std::vector<EntityHandle> HandleCont;

    static AsyncBehaviourManager* getInstance();
    EntityHandle    addEntity(AsyncBehaviour *e);
    void            eraseEntity(EntityHandle h); // 死亡を他 entity が察知できるようにするため、1 frame 遅延させる
    void            eraseEntityImmediate(EntityHandle h); // 1 frame の遅延抜きに直ちに消去する

    AsyncBehaviourManager(cpsObject o) : super(o) {}
    void Awake();
    void OnDestroy();
    void Update();

private:
    EntityCont m_entities;
    HandleCont m_all;
    HandleCont m_vacants;
    HandleCont m_dead;
    HandleCont m_dead_prev;
};


class AsyncBehaviour : public CppBehaviour
{
typedef CppBehaviour super;
friend class AsyncBehaviourManager;
public:
    AsyncBehaviour(cpsObject o) : super(o) {}
    virtual void BeforeAsyncUpdate();
    virtual void AsyncUpdate();
    virtual void AfterAsyncUpdate();

    EntityHandle getHandle() const { return m_handle; }

private:
    EntityHandle m_handle;
};

#endif // AsyncBehaviour_h
