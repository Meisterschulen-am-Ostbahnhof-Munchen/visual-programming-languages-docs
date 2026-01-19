# EC_START_ELEM

```{index} single: EC_START_ELEM
```

![EC_START_ELEM](https://user-images.githubusercontent.com/116869307/214154626-dbd925bc-19c1-4bbf-98f5-db588d7cefec.png)

* * * * * * * * * *

## Einleitung

Der EC_START_ELEM Funktionsblock dient zum Starten von Instanzen gemäß dem Zustandsautomaten von IEC 61499 Funktionsblöcken. Er ermöglicht das gezielte Starten von Funktionsblock-Instanzen, Verbindungen (Ereignis/Daten), Ressourcen oder Geräten innerhalb eines verteilten Automatisierungssystems.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Ereignis zum Anfordern des Starts eines Elements. Wird mit den Daten ELEM_NAME, DST und QI verknüpft.

### **Ereignis-Ausgänge**

- **CNF**: Ereignis zur Bestätigung, dass das Element gestartet wurde. Wird mit den Daten STATUS und QO verknüpft.

### **Daten-Eingänge**

- **QI** (BOOL): Ereignis-Eingangs-Qualifier zur Steuerung der Anforderung
- **ELEM_NAME** (WSTRING): Name der Elementinstanz, die gestartet werden soll
- **DST** (WSTRING): Zielort, an dem das Element gestartet werden muss (Syntax: ResourceName)

### **Daten-Ausgänge**

- **QO** (BOOL): Ereignis-Ausgangs-Qualifier zur Statusrückmeldung
- **STATUS** (WSTRING): Service-Status mit möglichen Werten: RDY, NO_SUCH_OBJECT, INVALID_STATE

### **Adapter**

Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise

Der Funktionsblock reagiert auf das REQ-Ereignis und versucht, das spezifizierte Element (Funktionsblock, Verbindung, Ressource oder Gerät) am angegebenen Zielort zu starten. Der Startvorgang erfolgt gemäß dem IEC 61499-Zustandsautomaten. Bei erfolgreichem Start wird das CNF-Ereignis mit dem Status "RDY" ausgegeben. Bei Fehlern werden entsprechende Statusmeldungen wie "NO_SUCH_OBJECT" oder "INVALID_STATE" zurückgegeben.

## Technische Besonderheiten

- Unterstützt Wide-String-Datentypen für Elementnamen und Zielorte
- Implementiert ein Qualifier-System zur Steuerung der Ausführungslogik
- Bietet detaillierte Statusrückmeldungen für verschiedene Fehlerzustände
- Folgt dem IEC 61499-Standard für Ausführungskontrollservices

## Zustandsübersicht

Der Funktionsblock verfügt über mehrere Service-Sequenzen:
- **normal_establishment**: Erfolgreiche Initialisierung
- **unsuccessful_establishment**: Fehlgeschlagene Initialisierung
- **request_confirm**: Erfolgreiche Anforderungsbearbeitung
- **request_inhibited**: Unterdrückte Anforderung
- **request_error**: Fehlerhafte Anforderungsbearbeitung
- **application_initiated_termination**: Anwendungsseitige Beendigung
- **resource_initiated_termination**: Ressourcenseitige Beendigung

## Anwendungsszenarien

- Dynamisches Starten von Funktionsblöcken in laufenden Systemen
- Rekonfiguration von Automatisierungssystemen zur Laufzeit
- Verteiltes Management von Ressourcen und Geräten
- Fehlertolerante Systeme mit Wiederanlauf-Funktionalität

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einfachen Start-Funktionsblöcken bietet EC_START_ELEM erweiterte Funktionalität für verteilte Systeme mit spezifischer Zielortangabe und detaillierter Statusrückmeldung. Er ist Teil der Rekonfigurationsservices und unterstützt verschiedene Elementtypen über reine Funktionsblöcke hinaus.

## Fazit

EC_START_ELEM ist ein leistungsstarker Funktionsblock für die dynamische Steuerung von Automatisierungssystemkomponenten. Seine Fähigkeit, verschiedene Elementtypen an spezifischen Zielorten zu starten, macht ihn besonders wertvoll für rekonfigurierbare und adaptive Steuerungssysteme gemäß IEC 61499.