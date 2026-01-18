# E_BLINK

```{index} single: E_BLINK
```

![E_BLINK Funktionsblock](https://github.com/user-attachments/assets/29d3de7c-a775-4796-9c22-096e97347a6e)

* * * * * * * * * *

## 🎧 Podcast

* [4diac IDE: Dein "Hello World" der Automatisierung – Das Blinking Tutorial Lokal](https://podcasters.spotify.com/pod/show/eclipse-4diac-de/episodes/4diac-IDE-Dein-Hello-World-der-Automatisierung--Das-Blinking-Tutorial-Lokal-e36971r)

## Einleitung
Der E_BLINK Funktionsblock simuliert ein blinkendes Signal, das zwischen den Zuständen TRUE und FALSE wechselt. Die Dauer der einzelnen Zustände kann individuell konfiguriert werden. Im Gegensatz zu ähnlichen Implementierungen kehrt dieser Funktionsblock beim STOP-Ereignis immer auf FALSE zurück.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **START**: Startet die periodische Generierung von Ereignissen. Verwendet die Daten `TIMELOW` und `TIMEHIGH`.
- **STOP**: Stoppt die Generierung von Ereignissen und setzt den Ausgang auf FALSE.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die Ausführung und liefert den aktuellen Ausgangswert `OUT`.

### **Daten-Eingänge**
- **TIMELOW**: Zeit in Millisekunden, während der der Ausgang FALSE ist.
- **TIMEHIGH**: Zeit in Millisekunden, während der der Ausgang TRUE ist.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert, der zwischen TRUE und FALSE wechselt.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der E_BLINK Funktionsblock verwendet intern einen E_PULSE Timer und einen E_CYCLE Generator, um die periodischen Zustandswechsel zu realisieren. Beim START-Ereignis werden die Zeiten für TRUE und FALSE addiert und als Zykluszeit für E_CYCLE verwendet. Der E_PULSE Timer steuert dann die Dauer des TRUE-Zustands, während die Differenzzeit den FALSE-Zustand bestimmt.

## Technische Besonderheiten
- Der Funktionsblock setzt den Ausgang beim STOP-Ereignis immer auf FALSE zurück.
- Die Implementierung unterscheidet sich von ähnlichen Lösungen wie CODESYS BLINK, die den letzten Zustand beibehalten.

## Zustandsübersicht
1. **Inaktiv**: Ausgang ist FALSE.
2. **Aktiv**: Ausgang wechselt periodisch zwischen TRUE und FALSE.
3. **Gestoppt**: Ausgang wird auf FALSE gesetzt.

## Anwendungsszenarien
- Steuerung von blinkenden Warnleuchten
- Generierung von Taktsignalen für Testzwecke
- Visualisierung von Zustandsänderungen in Bedienoberflächen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zum CODESYS BLINK Funktionsblock bietet E_BLINK eine vereinfachte Handhabung durch das automatische Zurücksetzen auf FALSE beim Stoppen. Die Funktionalität ist ähnlich, aber das Verhalten bei STOP ist konsistenter.

## Fazit
Der E_BLINK Funktionsblock bietet eine einfache und zuverlässige Möglichkeit, periodische Signale mit konfigurierbaren Ein- und Ausschaltzeiten zu generieren. Die klare Definition des STOP-Verhaltens macht ihn besonders für sicherheitsrelevante Anwendungen geeignet.