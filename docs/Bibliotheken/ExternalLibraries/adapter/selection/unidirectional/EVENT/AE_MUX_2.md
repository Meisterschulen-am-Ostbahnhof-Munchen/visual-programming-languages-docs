# AE_MUX_2


![AE_MUX_2](./AE_MUX_2.svg)

* * * * * * * * * *
## Einleitung

Der **AE_MUX_2** ist ein generischer Multiplexer-Funktionsblock für Analogwert-Adapter (AE). Er wählt anhand eines Indexeingangs einen von zwei analogen Signaleingängen aus und leitet diesen an den Ausgang weiter. Der Baustein ist nach dem Standard IEC 61499-2 aufgebaut und eignet sich für die flexible Signalumschaltung in verteilten Automatisierungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| REQ  | Event | Steuert die Aktualisierung des Index `K` und die Umschaltung des Ausgangs |

### **Ereignis-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| CNF  | Event | Quittierung nach erfolgter Umschaltung des Ausgangs |

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| K    | UINT | Index zur Auswahl des Eingangs (0 → IN1, 1 → IN2) |

### **Daten-Ausgänge**

Keine

### **Adapter**

| Funktion | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket   | IN1  | adapter::types::unidirectional::AE | Erster analoger Eingang (für K = 0) |
| Socket   | IN2  | adapter::types::unidirectional::AE | Zweiter analoger Eingang (für K = 1) |
| Plug     | OUT  | adapter::types::unidirectional::AE | Analoger Ausgang (entspricht IN1 oder IN2) |

## Funktionsweise

Der Baustein arbeitet als 2‑zu‑1‑Multiplexer auf Adapterebene. Sobald ein **REQ**-Ereignis eintrifft, wird der aktuelle Wert des Index `K` ausgewertet:
- Ist `K = 0`, wird der Adapter **IN1** auf den Ausgang **OUT** durchgeschaltet.
- Ist `K = 1`, wird der Adapter **IN2** auf den Ausgang **OUT** durchgeschaltet.

Nach erfolgreicher Umschaltung wird das **CNF**-Ereignis ausgegeben. Der Baustein ist ereignisgesteuert und führt nur bei einer steigenden Flanke an **REQ** eine Umschaltung durch.

## Technische Besonderheiten

- **Generische Klasse**: Der Funktionsblock wird durch das Attribut `GenericClassName = 'GEN_AE_MUX'` als generischer Baustein gekennzeichnet, was eine Wiederverwendung mit unterschiedlichen Adaptertypen ermöglicht.
- **Standardkonformität**: Vollständige Implementierung nach IEC 61499‑2, inklusive Metadaten für Identifikation und Versionierung.
- **Eingeschränkter Indexbereich**: Der Index `K` ist als `UINT` deklariert, die Logik implementiert jedoch nur die Werte 0 und 1; andere Werte führen zu undefiniertem Verhalten (abhängig von der konkreten Implementierung).
- **Unidirektionale Adapter**: Die verwendeten Adapter sind als unidirektional (`unidirectional`) definiert, d. h. die Daten fließen nur in eine Richtung.

## Zustandsübersicht

Der Baustein besitzt keine explizite Zustandsmaschine. Der Betrieb ist rein kombinatorisch: Jedes **REQ**-Ereignis löst eine sofortige Auswertung von `K` und die entsprechende Durchschaltung aus.

## Anwendungsszenarien

- **Umschaltung zwischen zwei analogen Sensoren** – z. B. Auswahl eines Temperaturfühlers aus zwei Messstellen.
- **Redundante Signalpfade** – bei Ausfall eines Eingangs kann auf den zweiten umgeschaltet werden.
- **Tests & Inbetriebnahme** – manuelles Umschalten zwischen einem realen und einem simulierten Analogwert.
- **Flexible Parametrierung** – der Index `K` kann dynamisch durch eine übergeordnete Steuerung gesetzt werden.

## Vergleich mit ähnlichen Bausteinen

| Merkmal | AE_MUX_2 | Standard IEC 61131 MUX | SE_MUX (für boolesche Signale) |
|---------|----------|------------------------|--------------------------------|
| **Datenart** | Analogwert (Adapter) | Einfache Datentypen | Boolesche Werte |
| **Anzahl Eingänge** | 2 | Mehrere (parametrierbar) | 2 |
| **Schnittstelle** | Adapter | Daten-Ein-/Ausgänge | Ereignis-/Daten-Ein-/Ausgänge |
| **Ereignissteuerung** | Ja (REQ/CNF) | Nein (zyklisch) | Ja |

Der AE_MUX_2 ist speziell für die Verwendung mit Analogwertadaptern optimiert und fügt sich nahtlos in die ereignisorientierte 4diac‑IDE‑Umgebung ein.

## Fazit

Der **AE_MUX_2** bietet eine kompakte und normgerechte Lösung zur Auswahl eines von zwei analogen Adaptersignalen. Dank seiner generischen Natur kann er in verschiedenen Automatisierungsprojekten eingesetzt werden, bei denen eine flexible und elegante Signalumschaltung auf Adapterebene erforderlich ist.