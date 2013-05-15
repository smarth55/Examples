import cgi #-------------------(this is template.py)--------------

class Engine(object):

  def __init__(self):
    # print "New engine created."
    self.input = cgi.FieldStorage()

  def execute(self): 
    s = self.retrieveState()
    if s.isEmpty() or self.reset():
      self.initializeState(s)
    else:
      self.updateState(s)
    self.saveState(s)
    self.reportState(s)
    self.getReadyforMoreInput()

  def retrieveState(self):
    return State()

  def initializeState(self, s): 
    pass

  def saveState(self, s):
    pass

  def reportState(self, s):
    pass

  def getReadyforMoreInput(self):
    pass

  def reset(self):
    return False

class State(object):
  def isEmpty(self):
    return True
