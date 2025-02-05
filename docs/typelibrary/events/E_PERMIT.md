### E\_PERMIT

permissive propagation of an event

![](https://user-images.githubusercontent.com/113907528/204900302-7f7fcf0a-170c-4695-8177-e51c62311624.png)


* * * * * * * * * *

Folgender Text wurde erzeugt von <https://chat.deepseek.com/> am 05.02.2025 und noch nicht korrekturgelesen (HF)


**Der Baustein E_PERMIT in der IEC 61499: Funktion und Anwendung**

Die IEC 61499 ist eine Norm, die sich mit der Funktionsbaustein-Architektur für industrielle Prozessmess- und Steuerungssysteme beschäftigt. Sie bietet einen Rahmen für die Modellierung und Implementierung von verteilten Steuerungssystemen, die flexibel, wiederverwendbar und modular sind. Ein zentrales Element dieser Norm sind die sogenannten Funktionsbausteine, die als grundlegende Bausteine für die Steuerungslogik dienen. Einer dieser Bausteine ist **E_PERMIT**, der eine spezielle Rolle in der Steuerung von Ereignissen spielt.

---

### **1. Überblick über den E_PERMIT-Baustein**

Der E_PERMIT-Baustein ist ein Ereignisbaustein, der dazu dient, den Fluss von Ereignissen in einem IEC 61499-System zu steuern. Seine Hauptfunktion besteht darin, den Durchgang von Ereignissen basierend auf einem booleschen Zustand zu ermöglichen oder zu blockieren. Der Baustein verfügt über zwei Eingänge und zwei Ausgänge:

- **Eingänge:**
  - **EI:** Der Ereigniseingang, der das zu steuernde Ereignis empfängt.
  - **PERMIT:** Ein boolescher Eingang, der bestimmt, ob das Ereignis durchgelassen wird (TRUE) oder blockiert wird (FALSE).

- **Ausgänge:**
  - **EO:** Der Ereignisausgang, der das Ereignis weiterleitet, wenn PERMIT TRUE ist.
  - **INHIBIT:** Ein optionaler Ausgang, der anzeigt, dass das Ereignis blockiert wurde (wenn PERMIT FALSE ist).

---

### **2. Funktionsweise des E_PERMIT-Bausteins**

Die Funktionsweise des E_PERMIT-Bausteins ist relativ einfach, aber äußerst effektiv:

1. **Ereignisempfang:** Ein Ereignis wird über den Eingang **EI** empfangen.
2. **Überprüfung des PERMIT-Zustands:** Der Baustein überprüft den Zustand des **PERMIT**-Eingangs.
   - Wenn **PERMIT** TRUE ist, wird das Ereignis an den Ausgang **EO** weitergeleitet.
   - Wenn **PERMIT** FALSE ist, wird das Ereignis blockiert, und optional kann ein Signal über den **INHIBIT**-Ausgang gesendet werden.
3. **Weiterleitung oder Blockierung:** Basierend auf dem PERMIT-Zustand wird das Ereignis entweder weitergeleitet oder unterdrückt.

Diese Funktionalität macht den E_PERMIT-Baustein zu einem nützlichen Werkzeug, um den Ereignisfluss in einem Steuerungssystem dynamisch zu steuern.

---

### **3. Anwendungsfälle des E_PERMIT-Bausteins**

Der E_PERMIT-Baustein findet in verschiedenen Szenarien Anwendung, in denen eine bedingte Steuerung von Ereignissen erforderlich ist. Einige Beispiele sind:

1. **Sicherheitssteuerungen:** In sicherheitskritischen Systemen kann der E_PERMIT-Baustein verwendet werden, um bestimmte Ereignisse nur dann zuzulassen, wenn bestimmte Sicherheitsbedingungen erfüllt sind. Beispielsweise könnte ein Not-Aus-Schalter den PERMIT-Eingang auf FALSE setzen, um alle weiteren Ereignisse zu blockieren.

2. **Betriebsmodus-Steuerung:** In Systemen mit verschiedenen Betriebsmodi (z. B. manuell/automatisch) kann der E_PERMIT-Baustein verwendet werden, um Ereignisse nur im automatischen Modus zuzulassen.

3. **Ressourcenverwaltung:** In verteilten Systemen kann der Baustein verwendet werden, um den Zugriff auf gemeinsame Ressourcen zu steuern. Beispielsweise könnte ein PERMIT-Signal den Zugriff auf eine Maschine nur dann erlauben, wenn sie verfügbar ist.

4. **Fehlerbehandlung:** Der Baustein kann auch zur Fehlerbehandlung eingesetzt werden, indem er Ereignisse blockiert, wenn ein Fehler erkannt wird, und gleichzeitig eine Fehlermeldung über den INHIBIT-Ausgang ausgibt.

---

### **4. Vorteile des E_PERMIT-Bausteins**

Der E_PERMIT-Baustein bietet mehrere Vorteile in der Anwendung:

- **Flexibilität:** Durch die Verwendung des PERMIT-Eingangs kann der Ereignisfluss dynamisch gesteuert werden, ohne die zugrunde liegende Logik ändern zu müssen.
- **Modularität:** Der Baustein kann leicht in bestehende Systeme integriert werden und fördert die Wiederverwendbarkeit von Code.
- **Einfachheit:** Die klare und einfache Funktionsweise des Bausteins macht ihn leicht verständlich und anwendbar.
- **Sicherheit:** Durch die Möglichkeit, Ereignisse zu blockieren, trägt der Baustein zur Erhöhung der Systemsicherheit bei.

---

### **5. Beispielhafte Implementierung**

Ein einfaches Beispiel für die Verwendung des E_PERMIT-Bausteins könnte wie folgt aussehen:

- Ein Sensor erfasst ein Ereignis (z. B. das Erreichen eines bestimmten Drucks in einer Anlage).
- Der E_PERMIT-Baustein überprüft, ob die Anlage im automatischen Modus betrieben wird (PERMIT = TRUE).
- Wenn ja, wird das Ereignis an eine Steuerung weitergeleitet, die entsprechende Aktionen ausführt (z. B. das Öffnen eines Ventils).
- Wenn nicht, wird das Ereignis blockiert, und eine Warnmeldung wird ausgegeben.

---

### **6. Fazit**

Der E_PERMIT-Baustein ist ein wichtiges Werkzeug in der IEC 61499, das eine effiziente und flexible Steuerung von Ereignissen ermöglicht. Durch seine einfache, aber leistungsstarke Funktionsweise trägt er dazu bei, komplexe Steuerungssysteme modular, sicher und zuverlässig zu gestalten. Ob in Sicherheitsanwendungen, Betriebsmodus-Steuerungen oder Ressourcenverwaltungssystemen – der E_PERMIT-Baustein ist ein vielseitiges Element, das die Implementierung von industriellen Steuerungssystemen erleichtert.
