/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef sitkObjectOwnedBase_h
#define sitkObjectOwnedBase_h


#include "sitkCommon.h"
#include "sitkNonCopyable.h"

#include <map>
#include <functional>


namespace itk
{

class Object;

namespace simple
{

/** \class ObjectOwnedBase
 * \brief  An abstract base class to connect this object with the lifetime of another.
 *
 * This class maintains a list of Objects and callbacks to call when this object is deleted.
 *
 * Optionally, "OwnedByObjects" property can be enabled so that when the last referenced object is removed this object
 * will be deleted.
 *
 *
 */
class SITKCommon_EXPORT ObjectOwnedBase
: public NonCopyable
{
public:
  virtual ~ObjectOwnedBase()
#ifndef SWIGR
    = 0
#endif
    ;

  ObjectOwnedBase() = default;

  /** Set object name. */
  virtual std::string
  GetName() const;

  /** Get object name. */
  virtual void
  SetName(const std::string & name);

protected:

  /** \brief Copy Constructor
   *
   * Only copiable if o does not have OwnedByObjects enabled. If OwnedByObjects is enabled in o, than an exception will
   * be thrown.
   *
   * The object callbacks are copied to the new object.
   */
  ObjectOwnedBase(const ObjectOwnedBase & o);


#ifndef SWIG
  /** \brief Register an Object and a method to call on this object's destructor.
   *
   * @param o
   * @param onDelete A function object to be called
   * @return The number of currently registered objects or functions.
   */
  virtual size_t
  AddObjectCallback(itk::Object *o, std::function<void()> onDelete);

  virtual size_t
  RemoveObject(const itk::Object *);


  /** Set/Get the OwnedByObject attribute.
   *
   * Indicates that ownership of this object is by object's in the ObjectCallbacks and that this object was dynamically
   * allocated on the heap.
   *
   * If true, when all objects have been removed by "RemovedObject", then this will be deleted.
   * @{
   */
  virtual void
  SetOwnedByObjects(bool o);
  virtual bool
  GetOwnedByObjects() const;
  virtual void
  OwnedByObjectsOn();
  virtual void
  OwnedByObjectsOff();
  /**@}*/
#endif


private:

  void ExecuteCallbacks(void);

  bool                                                m_OwnedByObjects{ false };
  std::multimap<itk::Object *, std::function<void()>> m_ReferencedObjectsCallbacks;
  std::string                                         m_Name;
};

} // namespace simple
} // namespace itk
#endif
