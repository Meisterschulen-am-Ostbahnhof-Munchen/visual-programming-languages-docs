# Q_ObjEnableDisable_AB


![Q_ObjEnableDisable_AB](./Q_ObjEnableDisable_AB.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `Q_ObjEnableDisable_AB` dient als Wrapper, der die Steuerung eines binären Objekts (Ein-/Ausschalten) über einen unidirektionalen **AB-Adapter (BYTE)** ermöglicht. Er kapselt die Logik des Bausteins `isobus::UT::Q::Q_ObjEnableDisable` und stellt dessen Funktionalität über die standardisierten Adapterschnittstellen `qAbility` (Socket) und `qOldAbility` (Plug) bereit. Der FB eignet sich zur Anbindung an Adapter-basierte Systeme, z. B. für die Fernsteuerung von Aktoren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Beschreibung |
|----------|-------|-------------|
| `INIT`   | EInit | Service-Initialisierung: startet den internen Baustein und übergibt die Objekt-ID. |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Beschreibung |
|----------|-------|-------------|
| `INITO`  | EInit | Bestätigung der erfolgreichen Initialisierung. |

### **Daten-Eingänge**

| Name       | Typ  | Beschreibung                  |
|------------|------|-------------------------------|
| `u16ObjId` | UINT | Eindeutige Identifikation des zu steuernden Objekts. |

### **Daten-Ausgänge**

Keine eigenen Datenausgänge – die Ausgangsdaten werden über den Adapter-Plug bereitgestellt.

### **Adapter**

| Adaptertyp                           | Richtung    | Beschreibung |
|--------------------------------------|-------------|-------------|
| **Socket** `qAbility`               | Eingang     | Unidirektionaler AB-Adapter: empfängt den Befehl (BYTE). `0` = deaktivieren, `1` = aktivieren, `0xFF` = undefiniert. |
| **Plug** `qOldAbility`              | Ausgang     | Unidirektionaler AB-Adapter: gibt den vorherigen Zustand des Objekts zurück (gleiche Codierung). |

## Funktionsweise

Der FB dient als Brücke zwischen einem AB-Adapter (BYTE) und dem internen Baustein `Q_ObjEnableDisable`. Die Abläufe sind:

1. **Initialisierung**  
   Ein INIT-Ereignis mit einer gültigen Objekt-ID (`u16ObjId`) wird an den internen FB weitergeleitet. Der interne FB wird initialisiert und meldet dies über `INITO` zurück.

2. **Steuerung**  
   Über den Socket `qAbility` wird ein BYTE-Wert empfangen. Das Ereignis `qAbility.E1` triggert den internen FB (Ereignis `REQ`). Der Datenwert aus `qAbility.D1` wird an den internen FB übergeben.  
   
   Der interne FB verarbeitet den Befehl und setzt den Zustand des Objekts entsprechend. Der vorherige Zustand wird über die interne Verbindung an den Plug `qOldAbility` weitergegeben. Das Ereignis `CNF` des internen FB wird als `qOldAbility.E1` ausgegeben.

3. **Rückmeldung**  
   Der Plug `qOldAbility` liefert den alten Zustand des Objekts (BYTE) und das zugehörige Ereignis, sodass ein nachgeschalteter Baustein auf Zustandsänderungen reagieren kann.

## Technische Besonderheiten

- **Adapter-Basierte Kapselung**  
  Der FB verwendet den standardisierten unidirektionalen AB-Adapter, wodurch er einfach in bestehende Adapter-Vernetzungen integriert werden kann.

- **Typische BYTE-Codierung**  
  `0` → deaktivieren, `1` → aktivieren, `0xFF` → undefiniert (Fehler oder keine Änderung). Diese Konvention wird sowohl am Eingang als auch am Ausgang verwendet.

- **Nur Initialisierung mit Objekt-ID**  
  Das INIT-Ereignis muss mit einer gültigen `u16ObjId` erfolgen. Der FB selbst speichert keine persistente Konfiguration.

- **Ereignisgesteuerte Verarbeitung**  
  Die Steuerung erfolgt ausschließlich über die Ereignisse des Adapter-Sockets. Ohne ein Ereignis auf `qAbility.E1` findet keine Zustandsänderung statt.

## Zustandsübersicht

Der FB besitzt keinen eigenen expliziten Zustandsautomaten – die Zustandslogik liegt vollständig im internen FB `Q_ObjEnableDisable`. Dennoch lassen sich folgende Betriebszustände ableiten:

| Zustand         | Beschreibung |
|-----------------|-------------|
| **Idle**        | Nach erfolgreicher Initialisierung (INITO gesendet) wartet der FB auf ein Ereignis am Socket `qAbility`. |
| **Processing**  | Ein eingehendes Ereignis auf `qAbility.E1` wird verarbeitet; der interne FB führt die Umschaltung aus. |
| **Completed**   | Verarbeitung abgeschlossen – der neue (bzw. alte) Zustand liegt am Plug an, Ereignis `qOldAbility.E1` wird ausgegeben. |

Fehlerzustände (z. B. ungültige Objekt-ID, fehlerhafte INIT-Sequenz) werden durch den internen FB behandelt und können über Rückgabewerte oder spezielle BYTE-Codes (`0xFF`) signalisiert werden.

## Anwendungsszenarien

- **Fernsteuerung eines Binärausgangs**  
  Ein übergeordneter Steuerungsbaustein sendet über einen AB-Adapter den Befehl „Ein“ oder „Aus“. Der FB setzt den Befehl um und meldet den vorherigen Zustand zurück.

- **Zustandsabfrage ohne Änderung**  
  Durch Senden des Codes `0xFF` kann der aktuelle Zustand abgefragt werden, ohne dass eine Änderung erfolgt.

- **Integration in Adapter-basierte Service-Interfaces**  
  Der FB dient als Konverter zwischen einem AB-Adapter (z. B. aus einem HMI oder einer Fernbedienung) und einem funktionalen Baustein, der natives ISOBUS-Interface benötigt.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Unterschied |
|----------|------------|
| `Q_ObjEnableDisable` (direkt) | Erfordert native Ereignis- und Datenschnittstellen ohne Adapter. `Q_ObjEnableDisable_AB` fügt die Adapter-Kompatibilität hinzu. |
| `Q_ObjEnableDisable_BB` (hypothetisch) | Würde einen bidirektionalen BB-Adapter verwenden. Der vorliegende FB verwendet den einfacheren unidirektionalen AB-Adapter. |
| Generischer „CommandOnOff“ | Ist typischerweise nicht auf ein spezifisches Objekt (ID) ausgerichtet und besitzt keine Zustandsrückmeldung über Adapter. |

## Fazit

Der FB `Q_ObjEnableDisable_AB` ist ein nützlicher Wrapper, der die Funktionalität eines ISOBUS-Objektschalters über den standardisierten AB-Adapter zugänglich macht. Er erleichtert die Integration in modulare Adapter-Netzwerke und reduziert den Verdrahtungsaufwand. Die einfache Schnittstelle mit nur einem Ereigniseingang zur Steuerung und einer Rückmeldung über den Plug macht ihn besonders geeignet für wiederverwendbare Komponenten in der Automatisierungstechnik.