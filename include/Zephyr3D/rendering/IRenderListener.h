#ifndef IRenderListener_h
#define IRenderListener_h

class IRenderListener {
public:
    IRenderListener() = default;
    IRenderListener(const IRenderListener&) = delete;
    IRenderListener& operator=(const IRenderListener&) = delete;
    IRenderListener(IRenderListener&&) = delete;
    IRenderListener& operator=(IRenderListener&&) = delete;
    virtual ~IRenderListener() = default;

    virtual void OnDrawObject() = 0;
};

#endif
