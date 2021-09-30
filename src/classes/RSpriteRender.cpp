#include "RSpriteRender.h"

#include "RayEngine.h"
#include <assert.h>

namespace RayCraft{

    RSpriteRender::RSpriteRender(const char *fileName,unsigned fps_tex,unsigned slots_x_tex,
                                    unsigned slots_y_tex,unsigned max_index_tex){

        fps=fps_tex;
        slots_x=slots_x_tex;
        slots_y=slots_y_tex;
        vramText =  LoadTexture(fileName);
        assert(vramText.height!=0);

        size_y = vramText.height / slots_y;
        size_x =vramText.width / slots_x;
        if(max_index_tex==0){
            max_index = slots_y*slots_x;
        }
        else{
            max_index = max_index_tex;
        }



    }

    void RSpriteRender::SetCurrentTextureIndex(unsigned index){
        if(index<max_index){
            texture_index = index;
        }
    }
    RSpriteRender::~RSpriteRender(){
        UnloadTexture(vramText);
    }

    void RSpriteRender::Draw(){
        Rectangle src;
        unsigned n;
        if(fps >0){
            n = (globalVariables.frameCounter*fps)/60;
            texture_index = n%max_index;
        }
        

        src.x = (texture_index%slots_x) * size_x;
        src.y = (texture_index%slots_y) * size_y;
        src.height = size_y;
        src.width = size_x;

        
        
        DrawTextureRec(vramText, src,parent->transform.location ,RAYWHITE);

    }






}