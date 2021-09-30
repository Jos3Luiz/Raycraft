#include "RComponent.h"

namespace RayCraft
{
    class RSpriteRender : public RComponent
    {

    public:
        RSpriteRender( const char *fileName,unsigned fps_tex=0,
                        unsigned slots_x_tex=1,unsigned slots_y_tex=1,unsigned max_index_tex=0);
        virtual ~RSpriteRender() override;

        virtual void Draw() override;

        void SetCurrentTextureIndex(unsigned index);
    private:

        //dimensions for the sprite
        unsigned size_x;
        unsigned size_y;
        unsigned slots_x;
        unsigned slots_y;
        unsigned texture_index=0;
        unsigned max_index=0;

        unsigned fps;
        Texture2D vramText;
    };

}