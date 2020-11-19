from pathlib import Path

import aiohttp_jinja2
import jinja2
from aiohttp import web

from routes import setup_routes

here = Path(__file__).resolve().parent

app = web.Application()
aiohttp_jinja2.setup(app, loader=jinja2.FileSystemLoader(str(here)))

setup_routes(app)
web.run_app(app, host="0.0.0.0", port=80)
