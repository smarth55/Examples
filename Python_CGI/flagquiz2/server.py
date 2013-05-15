import client, random, MySQLdb, sys

class Two(client.One):

  def retrieveState(self):
    if self.input.has_key("session_ID"): 
      id = self.input["session_ID"].value
      print "Content-type: text/html\n\n"
      print "Your id is:", id, "<p>"
      self.id = id 
      Con = MySQLdb.Connect(host="silo.cs.indiana.edu", port=17095, user="jleno", passwd="c4rs", db="ryan")
      Cursor = Con.cursor()  
      sql = "SELECT message, questions, correct, total, anskey FROM hwFour WHERE session_id = '%s'" % id
      Cursor.execute(sql)
      Results = Cursor.fetchall()
      (message, questions, correct, total, key) = Results[0]
      Con.close()
      return client.MyState(message, questions, str(correct), str(total), key)
    else: 
      print "Location: http://silo.cs.indiana.edu:16095/cgi-bin/0712/two?session_ID=%s\n\n" % self.generate_ID()
      sys.exit()

  def generate_ID(self): 
    id = ""
    for i in range(8):
      id += str(random.randrange(10))
    Con = MySQLdb.Connect(host="silo.cs.indiana.edu", port=17095, user="jleno", passwd="c4rs", db="ryan")
    Cursor = Con.cursor()  
    sql = "insert into hwFour (session_id) values ('" + id + "')"
    for i in range(10):
      if Cursor.execute(sql):
        Con.close()
        return id
    print "Content-type: text/html\n\nError. Please reload."
    Con.close()

  def saveState(self, s):
    sql = "update hwFour set message = '%s', questions = '%s', correct = '%s', total = '%s', anskey = '%s' where session_id = '%s'" % (s.message, s.questions, s.correct, s.total, s.key, self.id) 
    # print "<hr> %s <hr>" % sql 
    Con = MySQLdb.Connect(host="silo.cs.indiana.edu", port=17095, user="jleno", passwd="c4rs", db="ryan")
    Cursor = Con.cursor()  
    Cursor.execute(sql)
    Con.close()
    print "<form>"
    print "<input type=hidden name=session_ID value=\"%s\">" % self.id 
