import React from "react";
import Logo from "../assets/logo.svg";

import { Container, Form, Row, Col, Button } from "react-bootstrap";

export default function DeviceStatus() {
  return (
    <main
      style={{ background: "rgba(255, 203, 112, 0.34)" }}
      className="w-100 h-100"
    >
      <div className="text-center py-4">
        <img src={Logo} height={"110rem"} />
      </div>
      <hr />
      <section>
        <Container className="px-5">
          <Form>
            <Row>
              <Form.Group as={Col} md="12">
                <Form.Label>COACHING CENTER NAME</Form.Label>
                <Form.Control value="CHANAKYA SRINAGAR" />
              </Form.Group>
            </Row>

            <hr />

            <Row>
              <Form.Group as={Col} md="12">
                <Form.Label>CONFIGURED SCHEME NAME</Form.Label>
                <Form.Control value="PARVAAZ" />
              </Form.Group>
            </Row>

            <hr />

            <Row className="mt-1">
              <Form.Group as={Col} md="12">
                <Form.Label>DEVICE INFORMATION</Form.Label>
                <Form.Control value="MANTRA | MFS100" />
              </Form.Group>
            </Row>

            <hr />

            <div className="mx-4">
              <Row className="mt-1">
                <Form.Group as={Col} md="12">
                  <div className="d-flex justify-content-between align-items-end">
                    <div>SCANNER DEVICE STATUS</div>
                    <div className="mx-3">
                      <Button variant="success">CONNECTED</Button>
                    </div>
                  </div>
                </Form.Group>
              </Row>

              <hr />

              <Row className="mt-1">
                <Form.Group as={Col} md="12">
                  <div className="d-flex justify-content-between align-items-end">
                    <div>LOCAL SOCKET SERVER</div>
                    <div className="mx-3">
                      <Button variant="success">CONNECTED</Button>
                    </div>
                  </div>
                </Form.Group>
              </Row>
              <hr />

              <Row className="mt-1">
                <Form.Group as={Col} md="12">
                  <div className="d-flex justify-content-between align-items-end">
                    <div>ATTENDANCE SERVER STATUS</div>
                    <div className="mx-3">
                      <Button variant="danger">CONNECTED</Button>
                    </div>
                  </div>
                </Form.Group>
              </Row>
            </div>
          </Form>
        </Container>
      </section>
    </main>
  );
}
