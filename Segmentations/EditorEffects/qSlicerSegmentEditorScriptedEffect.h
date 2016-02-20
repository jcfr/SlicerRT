/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Laboratory for Percutaneous Surgery (PerkLab)
  Queen's University, Kingston, ON, Canada. All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Csaba Pinter, PerkLab, Queen's University
  and was supported through the Applied Cancer Research Unit program of Cancer Care
  Ontario with funds provided by the Ontario Ministry of Health and Long-Term Care

==============================================================================*/

#ifndef __qSlicerSegmentEditorScriptedEffect_h
#define __qSlicerSegmentEditorScriptedEffect_h

// Segmentations Editor Effects includes
#include "qSlicerSegmentEditorAbstractEffect.h"

#include "qSlicerSegmentationsEditorEffectsExport.h"

// Forward Declare PyObject*
#ifndef PyObject_HEAD
struct _object;
typedef _object PyObject;
#endif
class qSlicerSegmentEditorScriptedEffectPrivate;

/// \ingroup SlicerRt_QtModules_Segmentations
/// \brief Scripted abstract effect for implementing segment editor effects in python
///
/// This class provides an interface to effects implemented in python.
/// USAGE: Subclass AbstractScriptedSubjectHierarchyPlugin in SubjectHierarchyPlugins subfolder
///   of python scripted module, and register plugin by creating this class in module (e.g.
///   setup method of module widget) and setting python source to implemented plugin subclass.
///   Example can be found here: https://subversion.assembla.com/svn/slicerrt/trunk/VolumeClip/src
///
class Q_SLICER_SEGMENTATIONS_EFFECTS_EXPORT qSlicerSegmentEditorScriptedEffect
  : public qSlicerSegmentEditorAbstractEffect
{
  Q_OBJECT

public:
  typedef qSlicerSegmentEditorAbstractEffect Superclass;
  qSlicerSegmentEditorScriptedEffect(QObject* parent = NULL);
  virtual ~qSlicerSegmentEditorScriptedEffect();

  Q_INVOKABLE QString pythonSource()const;

  /// Set python source for the implemented plugin
  /// \param newPythonSource Python file path
  Q_INVOKABLE bool setPythonSource(const QString newPythonSource);

  /// Convenience method allowing to retrieve the associated scripted instance
  Q_INVOKABLE PyObject* self() const;

  /// Set the name property value.
  /// \sa name
  virtual void setName(QString name);

// API: Methods that are to be reimplemented in the effect subclasses
public:  
  /// Get icon for effect to be displayed in segment editor
  virtual QIcon icon();

  /// Get help text for effect to be displayed in the help box
  virtual const QString helpText()const;

  /// Clone editor effect. Override to return a new instance of the effect sub-class
  virtual qSlicerSegmentEditorAbstractEffect* clone();

  /// Perform actions to activate the effect (show options frame, etc.)
  virtual void activate();

  /// Perform actions to deactivate the effect (hide options frame, destroy actors, etc.)
  virtual void deactivate();

  /// Perform actions needed before the edited labelmap is applied back to the segment.
  /// Needs to be called from the python implementation to apply changes in the edited labelmap.
  Q_INVOKABLE virtual void apply();

  /// Create options frame widgets, make connections, and add them to the main options frame using \sa addOptionsWidget
  virtual void setupOptionsFrame();

  /// Create a cursor customized for the given effect, potentially for each view
  virtual QCursor createCursor(qMRMLWidget* viewWidget);

  /// Callback function invoked when interaction happens
  /// \param callerInteractor Interactor object that was observed to catch the event
  /// \param eid Event identifier
  /// \param viewWidget Widget of the Slicer layout view. Can be \sa qMRMLSliceWidget or \sa qMRMLThreeDWidget
  virtual void processInteractionEvents(vtkRenderWindowInteractor* callerInteractor, unsigned long eid, qMRMLWidget* viewWidget);

  /// Callback function invoked when view node is modified
  /// \param callerViewNode View node that was observed to catch the event. Can be either \sa vtkMRMLSliceNode or \sa vtkMRMLViewNode
  /// \param eid Event identifier
  /// \param viewWidget Widget of the Slicer layout view. Can be \sa qMRMLSliceWidget or \sa qMRMLThreeDWidget
  virtual void processViewNodeEvents(vtkMRMLAbstractViewNode* callerViewNode, unsigned long eid, qMRMLWidget* viewWidget);

  /// Set default parameters in the parameter MRML node
  virtual void setMRMLDefaults();

  /// Simple mechanism to let the effects know that edited labelmap has changed
  virtual void editedLabelmapChanged();
  /// Simple mechanism to let the effects know that master volume has changed
  virtual void masterVolumeNodeChanged();
  /// Simple mechanism to let the effects know that the layout has changed
  virtual void layoutChanged();

public slots:
  /// Update user interface from parameter set node
  virtual void updateGUIFromMRML();

  /// Update parameter set node from user interface
  virtual void updateMRMLFromGUI();

protected:
  QScopedPointer<qSlicerSegmentEditorScriptedEffectPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerSegmentEditorScriptedEffect);
  Q_DISABLE_COPY(qSlicerSegmentEditorScriptedEffect);
};

#endif
