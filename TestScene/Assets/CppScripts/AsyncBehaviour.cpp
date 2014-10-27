#include "AsyncBehaviour.h"
#include "tbb/tbb.h"

#define cpsCurrentClass AsyncBehaviourManager
cpsExportSingletonClass()
cpsExportMethod(Awake)
cpsExportMethod(OnDestroy)
cpsExportMethod(Update)
#undef cpsCurrentClass

#define cpsCurrentClass AsyncBehaviour
cpsExportClass()
cpsExportMethod(Awake)
cpsExportMethod(OnDestroy)
cpsExportMethod(BeforeAsyncUpdate)
cpsExportMethod(AsyncUpdate)
cpsExportMethod(AfterAsyncUpdate)
#undef cpsCurrentClass


static AsyncBehaviourManager* s_instance;

/*static*/ AsyncBehaviourManager* AsyncBehaviourManager::getInstance()
{
    if (!s_instance) {
        s_instance = new AsyncBehaviourManager(nullptr);
    }
    return s_instance;
}

void AsyncBehaviourManager::Awake()
{
}

void AsyncBehaviourManager::OnDestroy()
{
}

void AsyncBehaviourManager::Update()
{
    for (AsyncBehaviour *e : m_entities) {
        e->BeforeAsyncUpdate();
    }

    typedef tbb::blocked_range<size_t> range_t;
    tbb::parallel_for(
        range_t(size_t(0), m_entities.size(), 64),
        [&](const range_t &r){
            for (size_t i = r.begin(); i < r.end(); ++i) {
                m_entities[i]->AsyncUpdate();
            }
        });

    for (AsyncBehaviour *e : m_entities) {
        e->AfterAsyncUpdate();
    }
}



void AsyncBehaviour::Awake()
{
}

void AsyncBehaviour::OnDestroy()
{
}

void AsyncBehaviour::BeforeAsyncUpdate()
{
}

void AsyncBehaviour::AsyncUpdate()
{
}

void AsyncBehaviour::AfterAsyncUpdate()
{
}
