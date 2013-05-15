import template, random

class One(template.Engine):

  def __init__(self):
    template.Engine.__init__(self)

  def retrieveState(self):
    # print "I am retrieving state..."
    (message, questions, key, correct, total) = ("", "", "", "", "")
    if self.input.has_key("message"  ): message   = self.input["message"].value
    if self.input.has_key("questions"): questions = self.input["questions"].value
    if self.input.has_key("key"      ): key       = self.input["key"].value
    if self.input.has_key("correct"  ): correct   = self.input["correct"].value
    if self.input.has_key("total"    ): total     = self.input["total"].value
    return MyState(message, questions, correct, total, key)

  def reset(self):
    reset = ""
    if self.input.has_key("reset"): reset = self.input["reset"].value
    return reset

  def initializeState(self, s):
    # print "I am being asked to initialize the state..."
    s.message = "Welcome to the game, are you ready."
    names = ["Australia", "United States", "Russia", \
             "Spain", "Italy", "South Africa", "Brazil", "China"]
    random.shuffle(names)
    s.questions = ",".join(names)
    s.key = ""
    s.correct = "0"
    s.total = "0"

  def updateState(self, s):
    # print "I am being asked to update the state based on input..."
    (message, answer, url) = ("", "", "images")
    if self.input.has_key("answer"): answer = self.input["answer"].value
    if s.key: 
      if answer == s.key:
        s.message = "Very good."
        s.correct = str(int(s.correct) + 1)
      else:
        s.message = "No, no, no."
      s.total = str(int(s.total) + 1)
      s.message += "Score now: " + s.correct + " out of " + s.total
    else: 
      s.message = "Welcome to a new game, score currently: " + s.correct + " out of " + s.total + "."   
    if s.questions: 
      names = s.questions.split(",")
      (s.key, s.questions) = (names[0], ",".join(names[1:])) 
      s.question = "Whose country is this flag: <img src='%s/%s.png'> <input type=text name='answer'> <p>" % (url, s.key)
    else:
      temp = s.message
      self.initializeState(s) 
      s.message = temp 
      s.question = "The game has ended, new game starting, are you ready? <p>";    

  def saveState(self, s):
    print "<form>"
    print "<input type=hidden name=message value=\"" + s.message + "\">"
    print "<input type=hidden name=questions value=\"" + s.questions + "\">"
    print "<input type=hidden name=correct value=\"" + s.correct + "\">"
    print "<input type=hidden name=total value=\"" + s.total + "\">"
    print "<input type=hidden name=key value=\"" + s.key + "\">"

  def reportState(self, s):
    print s.message + "<p>"
    print s.question + "<p>"

  def getReadyforMoreInput(self):
    # print "Answer: <input type=text name=answer> <p>"
    print "Press <input type=submit name=submit value=Proceed> to move on <p>"
    print "Press <input type=submit name=reset value=Reset> to reset"
    print "</form>"

class MyState(template.State):
  def __init__(self, message, questions, correct, total, key):
    self.message = message
    self.questions = questions
    self.correct = correct
    self.total = total
    self.key = key
    self.question = "" # output
  def isEmpty(self):
    # print "I am being asked if I am empty..."
    return not self.message

