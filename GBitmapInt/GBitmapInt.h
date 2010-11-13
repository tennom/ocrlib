//C-
//C- This software is subject to, and may be distributed under, the
//C- GNU General Public License, either Version 2 of the license,
//C- or (at your option) any later version. The license should have
//C- accompanied the software or you may obtain a copy of the license
//C- from the Free Software Foundation at http://www.fsf.org .
//C-
//C- This program is distributed in the hope that it will be useful,
//C- but WITHOUT ANY WARRANTY; without even the implied warranty of
//C- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//C- GNU General Public License for more details.
//C-

//if ( ImBuf !=NULL ) farfree(ImBuf);  //  освобождение памяти
//q=(тип_q *)farmalloc(n_byte);     // запрос памяти без очистки 0
//q_new=farrealloc(q_old,n_byte);;  // изменение размера блока


#ifndef _GBitmapInt_H_
#define _GBitmapInt_H_
#include "config.h"




namespace ocr{

class  GBitmapInt {
protected:
  GBitmapInt(void);
  GBitmapInt(int nrows, int ncolumns, int border=0);
  GBitmapInt(const GBitmapInt *ref);
  GBitmapInt(const GBitmapInt *ref, int border);
 public:
  virtual ~GBitmapInt();
  void destroy(void);
  /** @name Construction. */
  //@{
  /** Constructs an empty GBitmapInt object.  The returned GBitmapInt has zero rows
      and zero columns.  Use function \Ref{init} to change the size of the
      image. */
  static GBitmapInt* create(void) {return new GBitmapInt;}

  /** Constructs a GBitmapInt with #nrows# rows and #ncolumns# columns.  All
      pixels are initialized to white. The optional argument #border#
      specifies the size of the optional border of white pixels surrounding
      the image.  The number of gray levels is initially set to #2#.  */
  static GBitmapInt* create(const int nrows, const int ncolumns, const int border=0)
  {return new GBitmapInt(nrows,ncolumns, border); }

  /** Copy constructor. Constructs a GBitmapInt by replicating the size, the
      border and the contents of GBitmapInt #ref#. */
  static GBitmapInt* create(const GBitmapInt* ref)
  {return new GBitmapInt(ref);}

  /** Constructs a GBitmapInt by copying the contents of GBitmapInt #ref#.  
      Argument #border# specifies the width of the optional border. */
  static GBitmapInt* create(const GBitmapInt* ref, const int border)
  { return new GBitmapInt(ref,border); }


  /** @name Initialization. */
  //@{
  /** Resets this GBitmapInt size to #nrows# rows and #ncolumns# columns and sets
	  all pixels to white.  The optional argument #border# specifies the size
	  of the optional border of white pixels surrounding the image.  The
	  number of gray levels is initialized to #2#. */
  void init(int nrows, int ncolumns, int border=0);
  /** Initializes this GBitmapInt with the contents of the GBitmapInt #ref#.  The
	  optional argument #border# specifies the size of the optional border of
	  white pixels surrounding the image. */
  void init(const GBitmapInt* ref, int border=0);
  /** Initializes this GBitmapInt with a rectangular segment #rect# of GBitmapInt
	  #ref#.  The optional argument #border# specifies the size of the
	  optional border of white pixels surrounding the image. */

  GBitmapInt* operator=(const GBitmapInt* ref);
  /** Initializes all the GBitmapInt pixels to value #value#. */
  void fill(unsigned int value);
  //@}

  /** @name Accessing the pixels. */
  //@{
  /** Returns the number of rows (the image height). */
  unsigned int rows() const;
  /** Returns the number of columns (the image width). */
  unsigned int columns() const;
  /** Returns a constant pointer to the first byte of row #row#.
	  This pointer can be used as an array to read the row elements. */
  const unsigned int *operator[] (int row) const;
  /** Returns a pointer to the first byte of row #row#.
	  This pointer can be used as an array to read or write the row elements. */
  unsigned int *operator[] (int row);
  /** Returns the size of a row in memory (in pixels).  This number is equal
	  to the difference between pointers to pixels located in the same column
	  in consecutive rows.  This difference can be larger than the number of
	  columns in the image. */
  unsigned int rowsize() const;
  /** Makes sure that the border is at least #minimum# pixels large.  This
	  function does nothing it the border width is already larger than
	  #minimum#.  Otherwise it reorganizes the data in order to provide a
	  border of #minimum# pixels. */
  void minborder(int minimum);
  void check_border();


protected:
  // bitmap components
  unsigned short nrows;
  unsigned short ncolumns;
  unsigned short border;
  unsigned short int_per_row;
  unsigned short grays;

public:
  unsigned int  *int_data;
  int data_size;
};

// ---------------- IMPLEMENTATION

inline unsigned int
GBitmapInt::rows() const
{
  return nrows;
}

inline unsigned int
GBitmapInt::columns() const
{
  return ncolumns;
}

inline unsigned int 
GBitmapInt::rowsize() const
{
  return int_per_row;
}


inline unsigned int *
GBitmapInt::operator[](int row)
{
  if (row<0 || row>=nrows) {
	return  int_data;
  }
  return &int_data[row * int_per_row + border];
}

inline const unsigned int *
GBitmapInt::operator[](int row) const
{
   if (row<0 || row>=nrows) {
	return int_data;
  }
  return &int_data[row * int_per_row + border];
}

inline GBitmapInt*
GBitmapInt::operator=(const GBitmapInt*ref)
{
  init(ref, ref->border);
  return this;
}

}
# endif

