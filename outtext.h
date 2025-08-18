 #ifndef _OUTTEXT_H_
#ifndef    _OUTTEXT_H_
#define    _OUTTEXT_H_


#include<GL/glut.h>
#include <string.h>
   


void
print_bitmap_string(void* font, char* s)
{
   if (s && strlen(s)) {
      while (*s) {
         glutStrokeCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *s);
         s++;
      }
   }
}

void
OutText (char* s)
{
  glPushMatrix();

      glScalef(0.001f, 0.001f,0);
   if (s && strlen(s)) {
      while (*s) {
         glutStrokeCharacter(GLUT_STROKE_ROMAN, *s);
         s++;
      }
   }
 glPopMatrix();
}



#endif 
