/**
 * Fuegt einem VORHANDENEN Google Form einen neuen Abschnitt mit 10 Fragen aus
 * Abkuerzungen_und_Bedeutungen.json hinzu (es wird kein neues Formular erstellt).
 *
 * Verwendung (Variante A, empfohlen): im Formular -> Drei-Punkte-Menue ->
 *   "Skript-Editor" oeffnen, Code einfuegen, "addAbkuerzungenSection" ausfuehren.
 * Variante B: eigenständiges Skript, FORM_ID unten eintragen
 *   (Teil der Formular-URL zwischen /d/ und /edit).
 */
var FORM_ID = ''; // nur fuer Variante B noetig
var SECTION_TITLE = 'Abkürzungen und Bedeutungen (IEC 61499 / 4diac / ISOBUS)';

function addAbkuerzungenSection() {
  var form = FORM_ID ? FormApp.openById(FORM_ID) : FormApp.getActiveForm();
  if (!form) throw new Error('Kein Formular gefunden: FORM_ID eintragen oder Skript aus dem Formular heraus oeffnen.');
  if (!form.isQuiz()) form.setIsQuiz(true); // noetig fuer Punkte/Feedback

  // Neuer Abschnitt am Ende des vorhandenen Formulars
  form.addPageBreakItem()
    .setTitle(SECTION_TITLE)
    .setHelpText('10 Fragen zu Datentypen, Bausteinen und Begriffen aus dem Glossar.');

  // Jede Frage: [Text, [Antworten], Index der richtigen Antwort, Erklärung]
  var questions = [
    ['Wie viele Bit hat der Standard-Datentyp BOOL?',
      ['1 Bit', '2 Bit', '8 Bit', '16 Bit'], 0,
      'BOOL ist eine boolesche Variable (1 Bit): FALSE/TRUE. 2 Bit hat QUARTER.'],

    ['Welche Größe hat der Datentyp DWORD (Doppelwort)?',
      ['8 Bit', '16 Bit', '32 Bit', '64 Bit'], 2,
      'BYTE = 8, WORD = 16, DWORD = 32, LWORD = 64 Bit.'],

    ['Wofür steht die Abkürzung AX bei einem Adapter-Interface?',
      ['1 Event, 1 Bool', '1 Event, 1 Word', '1 Event, 1 INT', '2 Events, 1 Bool'], 0,
      'AX = Unidirectional Adapter Interface (1 Event, 1 Bool). AW = Word, AI = INT.'],

    ['Welcher Funktionsbaustein ist ein Toggle-Flip-Flop (Stromstoßschalter)?',
      ['E_SR', 'E_T_FF', 'E_D_FF', 'E_RS'], 1,
      'E_T_FF = Toggle-Flip-Flop. E_SR ist ein Set-Reset-Flip-Flop, E_D_FF ein D-Latch.'],

    ['Welche Funktion hat der Baustein E_TON?',
      ['Ausschaltverzögerung', 'Impulsformung', 'Einschaltverzögerung', 'Ereigniszähler'], 2,
      'E_TON = Timer, einschaltverzögert (ereignisgesteuert).'],

    ['Was erkennt der Baustein E_R_TRIG?',
      ['Die fallende boolesche Flanke', 'Die steigende boolesche Flanke', 'Einen Zählerüberlauf', 'Einen Timeout'], 1,
      'E_R_TRIG = Erkennung der steigenden (Rising) Flanke, E_F_TRIG die der fallenden (Falling).'],

    ['Welche Funktion hat der Baustein E_CTUD?',
      ['Nur Aufwärtszähler', 'Nur Rückwärtszähler', 'Vor-/Rückwärtszähler', 'Verzögerungsschalter'], 2,
      'E_CTU = Aufwärts, E_CTD = Rückwärts, E_CTUD = Vor-/Rückwärtszähler.'],

    ['Was macht der Baustein E_CYCLE?',
      ['Erzeugt periodisch (zyklisch) ein Ereignis', 'Verzögert ein Ereignis einmalig', 'Demultiplext ein Ereignis', 'Erkennt eine Flanke'], 0,
      'E_CYCLE = periodische (zyklische) Erzeugung eines Ereignisses.'],

    ['Was beschreibt das Interface IX in der Hardware-/IO-Ebene?',
      ['Boolean Output', 'Event Input (1 Event)', 'Boolean Input (2 Events: drücken/loslassen)', 'Analoger Eingang'], 2,
      'IX = Input Bool Interface mit 2 Events (drücken/loslassen). QX = Boolean Output.'],

    ['Was bewirkt der ISOBUS-UT-Befehl Q_ActiveMask?',
      ['Change Attribute', 'Change Active Mask', 'Change Background Colour', 'Control Audio Signal'], 1,
      'Q_ActiveMask = ISOBUS UT Command: Change Active Mask.']
  ];

  questions.forEach(function (q) {
    var item = form.addMultipleChoiceItem();
    item.setTitle(q[0]);
    item.setRequired(true);
    item.setPoints(1);
    item.setChoices(q[1].map(function (text, i) {
      return item.createChoice(text, i === q[2]);
    }));
    item.setFeedbackForCorrect(FormApp.createFeedback().setText('Richtig! ' + q[3]).build());
    item.setFeedbackForIncorrect(FormApp.createFeedback().setText('Leider falsch. ' + q[3]).build());
  });

  Logger.log('Abschnitt hinzugefügt: ' + form.getEditUrl());
}
